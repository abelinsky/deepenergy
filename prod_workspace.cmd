@echo off
call start ./demo/Vesta/Vesta.exe
call ./agents/tensorboard_observe.bat 
call ./agents/tensorboard_server_start.bat
