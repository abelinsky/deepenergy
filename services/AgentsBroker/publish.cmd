@echo off
copy \apps\DeepEnergy\services\AgentsBroker\Release\AgentsBroker.exe \apps\DeepEnergy\demo\Vesta\AgentsBroker.exe /y
copy \apps\DeepEnergy\services\AgentsBroker\agentsbroker.ini \apps\DeepEnergy\demo\Vesta\agentsbroker.ini /y
copy \apps\DeepEnergy\services\AgentsBroker\agentsbroker.ini \apps\DeepEnergy\services\AgentsBroker\Debug\agentsbroker.ini /y
copy \apps\DeepEnergy\services\AgentsBroker\agentsbroker.ini \apps\DeepEnergy\services\AgentsBroker\Release\agentsbroker.ini /y


cmd /c copy \apps\DeepEnergy\services\AgentsBroker\Release\AgentsBroker.exe \apps\Garuda\release\AgentsBroker.exe /y
cmd /c copy \apps\DeepEnergy\services\AgentsBroker\Release\agentsbroker.ini \apps\Garuda\release\agentsbroker.ini /y
cmd /c copy \apps\DeepEnergy\services\AgentsBroker\Release\agentsbroker.ini \apps\Garuda\debug\AgentsBroker.exe /y
cmd /c copy \apps\DeepEnergy\services\AgentsBroker\Release\agentsbroker.ini \apps\Garuda\debug\agentsbroker.ini /y

