@echo off
call start cmd /k "cd /d D:\apps\DeepEnergy\simulators\gas\bin"
call start cmd /k "cd /d D:\apps\DeepEnergy\agents"
call code ./agents/
call code D:/apps/DeepEnergy/api/energyplatform 
call d:/apps/DeepEnergy/simulators/gas/src/EnvSimulatorGas/EnvSimulatorGas.sln
