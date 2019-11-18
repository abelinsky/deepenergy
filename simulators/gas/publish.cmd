@echo off
copy \apps\Galatea\simulators\gas\src\EnvSimulatorGas\Release\EnvSimulatorGas.exe \apps\Galatea\simulators\gas\bin\gasenv.exe /y
copy \apps\Galatea\simulators\gas\src\EnvSimulatorGas\Release\librdkafka.dll \apps\Galatea\simulators\gas\bin\librdkafka.dll /y
copy \apps\Galatea\simulators\gas\src\EnvSimulatorGas\Release\librdkafkacpp.dll \apps\Galatea\simulators\gas\bin\librdkafkacpp.dll /y
copy \apps\Galatea\simulators\gas\src\EnvSimulatorGas\Release\libzstd.dll \apps\Galatea\simulators\gas\bin\libzstd.dll /y
copy \apps\Galatea\simulators\gas\src\EnvSimulatorGas\Release\zlib.dll \apps\Galatea\simulators\gas\bin\zlib.dll /y