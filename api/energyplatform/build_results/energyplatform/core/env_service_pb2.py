# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: energyplatform/core/env_service.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from energyplatform.core import env_service_functions_pb2 as energyplatform_dot_core_dot_env__service__functions__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='energyplatform/core/env_service.proto',
  package='energyplatform',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n%energyplatform/core/env_service.proto\x12\x0e\x65nergyplatform\x1a/energyplatform/core/env_service_functions.proto2\xe8\x04\n\nEnvService\x12M\n\x08LoadData\x12\x1f.energyplatform.LoadDataRequest\x1a .energyplatform.LoadDataResponse\x12h\n\x11GetEnvDescription\x12(.energyplatform.GetEnvDescriptionRequest\x1a).energyplatform.GetEnvDescriptionResponse\x12_\n\x0eSetCurrentTask\x12%.energyplatform.SetCurrentTaskRequest\x1a&.energyplatform.SetCurrentTaskResponse\x12t\n\x15GetOptimizationParams\x12,.energyplatform.GetOptimizationParamsRequest\x1a-.energyplatform.GetOptimizationParamsResponse\x12\x44\n\x05Reset\x12\x1c.energyplatform.ResetRequest\x1a\x1d.energyplatform.ResetResponse\x12\x41\n\x04Step\x12\x1b.energyplatform.StepRequest\x1a\x1c.energyplatform.StepResponse\x12\x41\n\x04Stop\x12\x1b.energyplatform.StopRequest\x1a\x1c.energyplatform.StopResponseb\x06proto3')
  ,
  dependencies=[energyplatform_dot_core_dot_env__service__functions__pb2.DESCRIPTOR,])



_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_ENVSERVICE = _descriptor.ServiceDescriptor(
  name='EnvService',
  full_name='energyplatform.EnvService',
  file=DESCRIPTOR,
  index=0,
  serialized_options=None,
  serialized_start=107,
  serialized_end=723,
  methods=[
  _descriptor.MethodDescriptor(
    name='LoadData',
    full_name='energyplatform.EnvService.LoadData',
    index=0,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._LOADDATAREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._LOADDATARESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='GetEnvDescription',
    full_name='energyplatform.EnvService.GetEnvDescription',
    index=1,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._GETENVDESCRIPTIONREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._GETENVDESCRIPTIONRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='SetCurrentTask',
    full_name='energyplatform.EnvService.SetCurrentTask',
    index=2,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._SETCURRENTTASKREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._SETCURRENTTASKRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='GetOptimizationParams',
    full_name='energyplatform.EnvService.GetOptimizationParams',
    index=3,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._GETOPTIMIZATIONPARAMSREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._GETOPTIMIZATIONPARAMSRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='Reset',
    full_name='energyplatform.EnvService.Reset',
    index=4,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._RESETREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._RESETRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='Step',
    full_name='energyplatform.EnvService.Step',
    index=5,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._STEPREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._STEPRESPONSE,
    serialized_options=None,
  ),
  _descriptor.MethodDescriptor(
    name='Stop',
    full_name='energyplatform.EnvService.Stop',
    index=6,
    containing_service=None,
    input_type=energyplatform_dot_core_dot_env__service__functions__pb2._STOPREQUEST,
    output_type=energyplatform_dot_core_dot_env__service__functions__pb2._STOPRESPONSE,
    serialized_options=None,
  ),
])
_sym_db.RegisterServiceDescriptor(_ENVSERVICE)

DESCRIPTOR.services_by_name['EnvService'] = _ENVSERVICE

# @@protoc_insertion_point(module_scope)
