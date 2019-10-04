import org.apache.kafka.clients.producer.KafkaProducer;
import org.apache.kafka.clients.producer.ProducerRecord;

import java.util.Properties;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        final String KAFKA_SERVER_URL = "localhost";
        final int KAFKA_SERVER_PORT = 9092;

        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", KAFKA_SERVER_URL + ":" + KAFKA_SERVER_PORT);

        kafkaProps.put("key.serializer", "org.apache.kafka.common.serialization.StringSerializer");
        kafkaProps.put("value.serializer", "org.apache.kafka.common.serialization.StringSerializer");

        final KafkaProducer<String, String> producer = new KafkaProducer<String, String>(kafkaProps);

        while (true) {

            Scanner sc = new Scanner(System.in);
            String msg = sc.nextLine();
            if (msg.equals("exit"))
                break;

            ProducerRecord<String, String> record = new ProducerRecord<>("test", "Events", msg);

            try {
                producer.send(record);
            } catch (Exception e) {
                e.printStackTrace();
            }

            System.out.println("Hello!");

        }

    }
}
