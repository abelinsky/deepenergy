# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: unetwork/core/optimization_param.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from unetwork.core import types_pb2 as unetwork_dot_core_dot_types__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='unetwork/core/optimization_param.proto',
  package='unetwork',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n&unetwork/core/optimization_param.proto\x12\x08unetwork\x1a\x19unetwork/core/types.proto\"\xf2\x01\n\x1dOptimizationParameterMetadata\x12%\n\x04type\x18\x01 \x01(\x0e\x32\x17.unetwork.ParameterType\x12\x32\n\rphysical_type\x18\x02 \x01(\x0e\x32\x1b.unetwork.PhysicalValueType\x12\x34\n\x0e\x64iscrete_space\x18\x03 \x01(\x0b\x32\x1a.unetwork.DiscreteIntervalH\x00\x12\x37\n\x0f\x63ontinuos_space\x18\x04 \x01(\x0b\x32\x1c.unetwork.ContinuousIntervalH\x00\x42\x07\n\x05space\"\xa1\x01\n\x15OptimizationParameter\x12\x39\n\x08metadata\x18\x01 \x01(\x0b\x32\'.unetwork.OptimizationParameterMetadata\x12\n\n\x02id\x18\x02 \x01(\t\x12\x15\n\x0b\x66loat_value\x18\x03 \x01(\x02H\x00\x12\x13\n\tint_value\x18\x04 \x01(\x03H\x00\x12\x0c\n\x04info\x18\x05 \x01(\tB\x07\n\x05valueb\x06proto3')
  ,
  dependencies=[unetwork_dot_core_dot_types__pb2.DESCRIPTOR,])




_OPTIMIZATIONPARAMETERMETADATA = _descriptor.Descriptor(
  name='OptimizationParameterMetadata',
  full_name='unetwork.OptimizationParameterMetadata',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='unetwork.OptimizationParameterMetadata.type', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='physical_type', full_name='unetwork.OptimizationParameterMetadata.physical_type', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='discrete_space', full_name='unetwork.OptimizationParameterMetadata.discrete_space', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='continuos_space', full_name='unetwork.OptimizationParameterMetadata.continuos_space', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='space', full_name='unetwork.OptimizationParameterMetadata.space',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=80,
  serialized_end=322,
)


_OPTIMIZATIONPARAMETER = _descriptor.Descriptor(
  name='OptimizationParameter',
  full_name='unetwork.OptimizationParameter',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='metadata', full_name='unetwork.OptimizationParameter.metadata', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='id', full_name='unetwork.OptimizationParameter.id', index=1,
      number=2, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='float_value', full_name='unetwork.OptimizationParameter.float_value', index=2,
      number=3, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=float(0),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='int_value', full_name='unetwork.OptimizationParameter.int_value', index=3,
      number=4, type=3, cpp_type=2, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='info', full_name='unetwork.OptimizationParameter.info', index=4,
      number=5, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='value', full_name='unetwork.OptimizationParameter.value',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=325,
  serialized_end=486,
)

_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['type'].enum_type = unetwork_dot_core_dot_types__pb2._PARAMETERTYPE
_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['physical_type'].enum_type = unetwork_dot_core_dot_types__pb2._PHYSICALVALUETYPE
_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['discrete_space'].message_type = unetwork_dot_core_dot_types__pb2._DISCRETEINTERVAL
_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['continuos_space'].message_type = unetwork_dot_core_dot_types__pb2._CONTINUOUSINTERVAL
_OPTIMIZATIONPARAMETERMETADATA.oneofs_by_name['space'].fields.append(
  _OPTIMIZATIONPARAMETERMETADATA.fields_by_name['discrete_space'])
_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['discrete_space'].containing_oneof = _OPTIMIZATIONPARAMETERMETADATA.oneofs_by_name['space']
_OPTIMIZATIONPARAMETERMETADATA.oneofs_by_name['space'].fields.append(
  _OPTIMIZATIONPARAMETERMETADATA.fields_by_name['continuos_space'])
_OPTIMIZATIONPARAMETERMETADATA.fields_by_name['continuos_space'].containing_oneof = _OPTIMIZATIONPARAMETERMETADATA.oneofs_by_name['space']
_OPTIMIZATIONPARAMETER.fields_by_name['metadata'].message_type = _OPTIMIZATIONPARAMETERMETADATA
_OPTIMIZATIONPARAMETER.oneofs_by_name['value'].fields.append(
  _OPTIMIZATIONPARAMETER.fields_by_name['float_value'])
_OPTIMIZATIONPARAMETER.fields_by_name['float_value'].containing_oneof = _OPTIMIZATIONPARAMETER.oneofs_by_name['value']
_OPTIMIZATIONPARAMETER.oneofs_by_name['value'].fields.append(
  _OPTIMIZATIONPARAMETER.fields_by_name['int_value'])
_OPTIMIZATIONPARAMETER.fields_by_name['int_value'].containing_oneof = _OPTIMIZATIONPARAMETER.oneofs_by_name['value']
DESCRIPTOR.message_types_by_name['OptimizationParameterMetadata'] = _OPTIMIZATIONPARAMETERMETADATA
DESCRIPTOR.message_types_by_name['OptimizationParameter'] = _OPTIMIZATIONPARAMETER
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

OptimizationParameterMetadata = _reflection.GeneratedProtocolMessageType('OptimizationParameterMetadata', (_message.Message,), {
  'DESCRIPTOR' : _OPTIMIZATIONPARAMETERMETADATA,
  '__module__' : 'unetwork.core.optimization_param_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.OptimizationParameterMetadata)
  })
_sym_db.RegisterMessage(OptimizationParameterMetadata)

OptimizationParameter = _reflection.GeneratedProtocolMessageType('OptimizationParameter', (_message.Message,), {
  'DESCRIPTOR' : _OPTIMIZATIONPARAMETER,
  '__module__' : 'unetwork.core.optimization_param_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.OptimizationParameter)
  })
_sym_db.RegisterMessage(OptimizationParameter)


# @@protoc_insertion_point(module_scope)
