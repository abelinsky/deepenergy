# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: api/core/action.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from api.core import optimization_param_pb2 as api_dot_core_dot_optimization__param__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='api/core/action.proto',
  package='api',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x15\x61pi/core/action.proto\x12\x03\x61pi\x1a!api/core/optimization_param.proto\"O\n\x06\x41\x63tion\x12\x37\n\x13optimization_params\x18\x01 \x03(\x0b\x32\x1a.api.OptimizationParameter\x12\x0c\n\x04info\x18\x02 \x01(\tb\x06proto3')
  ,
  dependencies=[api_dot_core_dot_optimization__param__pb2.DESCRIPTOR,])




_ACTION = _descriptor.Descriptor(
  name='Action',
  full_name='api.Action',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='optimization_params', full_name='api.Action.optimization_params', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='info', full_name='api.Action.info', index=1,
      number=2, type=9, cpp_type=9, label=1,
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
  ],
  serialized_start=65,
  serialized_end=144,
)

_ACTION.fields_by_name['optimization_params'].message_type = api_dot_core_dot_optimization__param__pb2._OPTIMIZATIONPARAMETER
DESCRIPTOR.message_types_by_name['Action'] = _ACTION
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Action = _reflection.GeneratedProtocolMessageType('Action', (_message.Message,), {
  'DESCRIPTOR' : _ACTION,
  '__module__' : 'api.core.action_pb2'
  # @@protoc_insertion_point(class_scope:api.Action)
  })
_sym_db.RegisterMessage(Action)


# @@protoc_insertion_point(module_scope)
