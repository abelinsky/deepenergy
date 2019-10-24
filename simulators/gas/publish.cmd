@echo off
copy \apps\DeepEnergy\simulators\gas\src\EnvSimulatorGas\Release\EnvSimulatorGas.exe \apps\DeepEnergy\simulators\gas\bin\gasenv.exe /y
copy \apps\DeepEnergy\simulators\gas\src\EnvSimulatorGas\Release\librdkafka.dll \apps\DeepEnergy\simulators\gas\bin\librdkafka.dll /y
copy \apps\DeepEnergy\simulators\gas\src\EnvSimulatorGas\Release\librdkafkacpp.dll \apps\DeepEnergy\simulators\gas\bin\librdkafkacpp.dll /y
copy \apps\DeepEnergy\simulators\gas\src\EnvSimulatorGas\Release\libzstd.dll \apps\DeepEnergy\simulators\gas\bin\libzstd.dll /y
copy \apps\DeepEnergy\simulators\gas\src\EnvSimulatorGas\Release\zlib.dll \apps\DeepEnergy\simulators\gas\bin\zlib.dll /y