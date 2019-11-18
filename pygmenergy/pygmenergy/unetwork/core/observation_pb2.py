# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: unetwork/core/observation.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from pygmenergy.unetwork.core import types_pb2 as unetwork_dot_core_dot_types__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='unetwork/core/observation.proto',
  package='unetwork',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x1funetwork/core/observation.proto\x12\x08unetwork\x1a\x19unetwork/core/types.proto\"5\n\x0bObservation\x12&\n\x05items\x18\x01 \x03(\x0b\x32\x17.unetwork.PhysicalParamb\x06proto3')
  ,
  dependencies=[unetwork_dot_core_dot_types__pb2.DESCRIPTOR,])




_OBSERVATION = _descriptor.Descriptor(
  name='Observation',
  full_name='unetwork.Observation',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='items', full_name='unetwork.Observation.items', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=72,
  serialized_end=125,
)

_OBSERVATION.fields_by_name['items'].message_type = unetwork_dot_core_dot_types__pb2._PHYSICALPARAM
DESCRIPTOR.message_types_by_name['Observation'] = _OBSERVATION
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Observation = _reflection.GeneratedProtocolMessageType('Observation', (_message.Message,), {
  'DESCRIPTOR' : _OBSERVATION,
  '__module__' : 'unetwork.core.observation_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.Observation)
  })
_sym_db.RegisterMessage(Observation)


# @@protoc_insertion_point(module_scope)
