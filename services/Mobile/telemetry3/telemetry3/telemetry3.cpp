// telemetry3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>

#include <algorithm>
#include <ctime>
#include "firebase/app.h"
#include "firebase/auth.h"
#include "firebase/database.h"
#include "firebase/future.h"
#include "firebase/util.h"

#ifdef _WIN32
#include <windows.h>
#endif  // _WIN32

using namespace std;


/*****************************************  Kafka producer  *****************************************/
#include <librdkafka/rdkafkacpp.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>

static bool run = true;
static bool exit_eof = false;

static void sigterm(int sig) {
	run = false;
}

class ExampleDeliveryReportCb : public RdKafka::DeliveryReportCb {
public:
	void dr_cb(RdKafka::Message &message) {
		std::string status_name;
		switch (message.status())
		{
		case RdKafka::Message::MSG_STATUS_NOT_PERSISTED:
			status_name = "NotPersisted";
			break;
		case RdKafka::Message::MSG_STATUS_POSSIBLY_PERSISTED:
			status_name = "PossiblyPersisted";
			break;
		case RdKafka::Message::MSG_STATUS_PERSISTED:
			status_name = "Persisted";
			break;
		default:
			status_name = "Unknown?";
			break;
		}
		std::cout << "Message delivery for (" << message.len() << " bytes): " <<
			status_name << ": " << message.errstr() << std::endl;
		if (message.key())
			std::cout << "Key: " << *(message.key()) << ";" << std::endl;
	}
};

RdKafka::Producer* CreateKafkaProducer() {
	/*
	 * Create Kafka producer using accumulated global configuration.
	 */
	std::string brokers = "localhost:9092";
	std::string errstr;

	int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING;
	bool do_conf_dump = false;

	// create configuration objects
	RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
	RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

	signal(SIGINT, sigterm);
	signal(SIGTERM, sigterm);

	// set configuration properties
	conf->set("metadata.broker.list", brokers, errstr);

	ExampleDeliveryReportCb ex_dr_cb;
	/* Set delivery report callback */
	conf->set("dr_cb", &ex_dr_cb, errstr);
	conf->set("default_topic_conf", tconf, errstr);
	/*
	 * Create producer using accumulated global configuration.
	 */
	RdKafka::Producer *producer = RdKafka::Producer::create(conf, errstr);
	if (!producer) {
		std::cerr << "Failed to create producer: " << errstr << std::endl;
		exit(1);
	}

	std::cout << "% Created producer " << producer->name() << std::endl;


	return producer;
}

/***************************** Firebase stuff **********************************/
void LogMessage(const char* format, ...) {
	va_list list;
	va_start(list, format);
	vprintf(format, list);
	va_end(list);
	printf("\n");
	fflush(stdout);
}

static bool quit = false;

bool ProcessEvents(int msec) {
#ifdef _WIN32
	Sleep(msec);
#else
	usleep(msec * 1000);
#endif  // _WIN32
	return quit;
}

// Path to the Firebase config file to load.
#ifdef FIREBASE_CONFIG
#define FIREBASE_CONFIG_STRING TO_STRING(FIREBASE_CONFIG)
#else
#define FIREBASE_CONFIG_STRING ""
#endif  // FIREBASE_CONFIG

// An example of a ValueListener object. This specific version will
// simply log every value it sees, and store them in a list so we can
// confirm that all values were received.
class SampleValueListener : public firebase::database::ValueListener {
protected:	
	RdKafka::Producer *kafka_producer_;
	std::string topic_name_;
	int32_t partition_;

public:
	SampleValueListener(RdKafka::Producer *kafka_producer, const std::string topic_name, int32_t partition) {
		kafka_producer_ = kafka_producer;
		topic_name_ = topic_name;
		partition_ = partition;
	}

	void OnValueChanged(
		const firebase::database::DataSnapshot& snapshot) override {
		double value = snapshot.value().AsDouble().double_value();
		std::string str_value = snapshot.value().AsString().string_value();

		std::cout << "valueeeeee " << value << endl;

		LogMessage("  New event (%s)",
			snapshot.value().AsString().string_value());

		if (kafka_producer_) {
			//RdKafka::Headers *headers = RdKafka::Headers::create();
			//headers->add("event", "FirebaseEvent");

			/*
			 * Produce message
			 */
			RdKafka::ErrorCode resp =
				kafka_producer_->produce(topic_name_, partition_,
					RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
					/* Value */
					//const_cast<char *>(line.c_str()), line.size(),
					const_cast<char*>(str_value.c_str()), str_value.size(),
					/* Key */
					NULL, 0,
					/* Timestamp (defaults to now) */
					0,
					/* Message headers, if any */
					NULL,
					/* Per-message opaque value passed to
					 * delivery report */
					NULL);

			if (resp != RdKafka::ERR_NO_ERROR) {
				std::cout << "% Produce failed: " <<
					RdKafka::err2str(resp) << std::endl;
				//delete headers; /* Headers are automatically deleted on produce()
								 // * success. */
			}
			else {
				std::cerr << "% Produced message (" << sizeof(value) << " bytes)" <<
					std::endl;
			}

			//kafka_producer_->poll(0);
		}

		last_seen_value_ = snapshot.value();
		seen_values_.push_back(snapshot.value());
	}
	void OnCancelled(const firebase::database::Error& error_code,
		const char* error_message) override {
		LogMessage("ERROR: SampleValueListener canceled: %d: %s", error_code,
			error_message);
	}
	const firebase::Variant& last_seen_value() { return last_seen_value_; }
	bool seen_value(const firebase::Variant& value) {
		return std::find(seen_values_.begin(), seen_values_.end(), value) !=
			seen_values_.end();
	}
	size_t num_seen_values() { return seen_values_.size(); }

private:
	firebase::Variant last_seen_value_;
	std::vector<firebase::Variant> seen_values_;
};


// Wait for a Future to be completed. If the Future returns an error, it will
// be logged.
void WaitForCompletion(const firebase::FutureBase& future, const char* name) {
	while (future.status() == firebase::kFutureStatusPending) {
		ProcessEvents(100);
	}
	if (future.status() != firebase::kFutureStatusComplete) {
		LogMessage("ERROR: %s returned an invalid result.", name);
	}
	else if (future.error() != 0) {
		LogMessage("ERROR: %s returned error %d: %s", name, future.error(),
			future.error_message());
	}
}


/*****************************************  Main  *****************************************/
int main()
{
	::firebase::App* app;

#if defined(__ANDROID__)
	app = ::firebase::App::Create(GetJniEnv(), GetActivity());
#else
	app = ::firebase::App::Create();
#endif  // defined(__ANDROID__)

	LogMessage("Initialized Firebase App.");

	LogMessage("Initialize Firebase Auth and Firebase Database.");

	// Use ModuleInitializer to initialize both Auth and Database, ensuring no
	// dependencies are missing.
	::firebase::database::Database* database = nullptr;
	::firebase::auth::Auth* auth = nullptr;
	void* initialize_targets[] = { &auth, &database };

	const firebase::ModuleInitializer::InitializerFn initializers[] = {
		[](::firebase::App* app, void* data) {
		  LogMessage("Attempt to initialize Firebase Auth.");
		  void** targets = reinterpret_cast<void**>(data);
		  ::firebase::InitResult result;
		  *reinterpret_cast<::firebase::auth::Auth**>(targets[0]) =
			  ::firebase::auth::Auth::GetAuth(app, &result);
		  return result;
		},
		[](::firebase::App* app, void* data) {
		  LogMessage("Attempt to initialize Firebase Database.");
		  void** targets = reinterpret_cast<void**>(data);
		  ::firebase::InitResult result;
		  *reinterpret_cast<::firebase::database::Database**>(targets[1]) =
			  ::firebase::database::Database::GetInstance(app, &result);
		  return result;
		} };

	::firebase::ModuleInitializer initializer;
	initializer.Initialize(app, initialize_targets, initializers,
		sizeof(initializers) / sizeof(initializers[0]));

	WaitForCompletion(initializer.InitializeLastResult(), "Initialize");

	if (initializer.InitializeLastResult().error() != 0) {
		LogMessage("Failed to initialize Firebase libraries: %s",
			initializer.InitializeLastResult().error_message());
		ProcessEvents(2000);
		return 1;
	}
	LogMessage("Successfully initialized Firebase Auth and Firebase Database.");

	database->set_persistence_enabled(true);

	// Sign in using Auth before accessing the database.
	// The default Database permissions allow anonymous users access. This will
	// work as long as your project's Authentication permissions allow anonymous
	// signin.
	{
		firebase::Future<firebase::auth::User*> sign_in_future =
			auth->SignInAnonymously();
		WaitForCompletion(sign_in_future, "SignInAnonymously");
		if (sign_in_future.error() == firebase::auth::kAuthErrorNone) {
			LogMessage("Auth: Signed in anonymously.");
		}
		else {
			LogMessage("ERROR: Could not sign in anonymously. Error %d: %s",
				sign_in_future.error(), sign_in_future.error_message());
			LogMessage(
				"  Ensure your application has the Anonymous sign-in provider "
				"enabled in Firebase Console.");
			LogMessage(
				"  Attempting to connect to the database anyway. This may fail "
				"depending on the security settings.");
		}
	}

	std::string saved_url;  // persists across connections
	  // Create a unique child in the database that we can run our tests in.
	firebase::database::DatabaseReference ref;
	ref = database->GetReference("Events/GasFieldEvent");

	saved_url = ref.url();
	LogMessage("URL: %s", saved_url.c_str());


	// Create Kafka producer
	RdKafka::Producer *producer = CreateKafkaProducer();
	std::string topic_str = "telemetry";
	int32_t partition = 0; // RdKafka::Topic::PARTITION_UA;

	// ValueListener, which sits on a Query and listens for changes in
	  // the value at that location.
	LogMessage("Listening to events in database...");
	SampleValueListener* listener = new SampleValueListener(producer, topic_str, partition);
	//WaitForCompletion(ref.Child("GasFieldEvent").SetValue(0), "InitializeEventsListener");
	ref.AddValueListener(listener);
	//ref.Child("GasFieldEvent").AddValueListener(listener);

	LogMessage("For exit press q");
	char k;

	while (!ProcessEvents(1000)) {
		// The listener's OnChanged callback is triggered once when the listener is
		// attached and again every time the data, including children, changes.
		// Wait for here for a moment for the initial values to be received.

		std::cin >> k;
		if (k == 'q') {
			quit = true;
		}
	}

	delete listener;

	LogMessage("Shutdown the Database library.");
	delete database;
	database = nullptr;

	LogMessage("Signing out from anonymous account.");
	auth->SignOut();
	LogMessage("Shutdown the Auth library.");
	delete auth;
	auth = nullptr;

	LogMessage("Shutdown Firebase App.");
	delete app;

	LogMessage("Shutdown Kafka producer.");
	while (run && producer->outq_len() > 0) {
		std::cerr << "Waiting for " << producer->outq_len() << std::endl;
		producer->poll(1000);
	}
	delete producer;
}
