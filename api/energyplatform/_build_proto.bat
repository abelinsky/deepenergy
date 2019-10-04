@echo off

REM Builds proto file and outputs cpp and python sources.
REM First argument: root directory where to search for imported files defined in the compiled *.proto file
REM Second argument: *.proto file path
REM Third argument: dir for the build results
REM Example: build_proto.bat core/Env.proto build_results/core

set GRPC_INSTALLED_PATH=/apps/tools/gRPC/vcpkg/installed/x86-windows-static/tools
set BUILDER=%GRPC_INSTALLED_PATH%/protobuf/protoc.exe
set GRPC_CPP_PLUGIN=%GRPC_INSTALLED_PATH%/grpc/grpc_cpp_plugin.exe
set GRPC_PYTHON_PLUGIN=%GRPC_INSTALLED_PATH%/grpc/grpc_python_plugin.exe

%BUILDER% --proto_path=%~dp1 --cpp_out=%3 %~f2
%BUILDER% --proto_path=%~dp1 --grpc_out=%3 --plugin=protoc-gen-grpc=%GRPC_CPP_PLUGIN% %~f2

%BUILDER% --proto_path=%~dp1 --python_out=%3 %~f2
%BUILDER% --proto_path=%~dp1 --grpc_out=%3 --plugin=protoc-gen-grpc=%GRPC_PYTHON_PLUGIN% %~f2
