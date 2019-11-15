@echo off
rem set PATH="%~dp0"
REM Start the zookeeper on the default port which is 2181
start cmd /k zkserver
REM Running Apache Kafka (By default Apache Kafka will run on port 9092)
start cmd /k "%KAFKA_HOME%/bin/windows/kafka-server-start.bat %KAFKA_HOME%/config/server.properties"
REM Start a consumer to test Kafka events
start cmd /k "%KAFKA_HOME%/bin/windows/kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic telemetry --from-beginning"
REM Start consumer of telemetry events (currently from Firebase), that produces events to Kafka (it's like Kafka Connect)
call cd "services/Mobile/telemetry3/Release" & start cmd /k "telemetry3.exe"
REM Start simulator
call cd "%~dp0" & start ../Garuda/Release/Vesta.exe
REM Run Predictor service (Model serving)
start cmd /k "C:/Users/ab/Anaconda3/envs/grpcenv/python.exe ./agents/predictor_service.py"