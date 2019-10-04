# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: energyplatform/core/observation.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from energyplatform.core import graph_pb2 as energyplatform_dot_core_dot_graph__pb2


DESCRIPTOR = _descriptor.FileDescriptor(
  name='energyplatform/core/observation.proto',
  package='energyplatform',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n%energyplatform/core/observation.proto\x12\x0e\x65nergyplatform\x1a\x1f\x65nergyplatform/core/graph.proto\"\xa3\x02\n\x0bObservation\x12@\n\x0bnode_values\x18\x01 \x03(\x0b\x32+.energyplatform.Observation.NodeValuesEntry\x12@\n\x0b\x65\x64ge_values\x18\x02 \x03(\x0b\x32+.energyplatform.Observation.EdgeValuesEntry\x1aG\n\x0fNodeValuesEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.energyplatform.Node:\x02\x38\x01\x1aG\n\x0f\x45\x64geValuesEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12#\n\x05value\x18\x02 \x01(\x0b\x32\x14.energyplatform.Edge:\x02\x38\x01\x62\x06proto3')
  ,
  dependencies=[energyplatform_dot_core_dot_graph__pb2.DESCRIPTOR,])




_OBSERVATION_NODEVALUESENTRY = _descriptor.Descriptor(
  name='NodeValuesEntry',
  full_name='energyplatform.Observation.NodeValuesEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='energyplatform.Observation.NodeValuesEntry.key', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='energyplatform.Observation.NodeValuesEntry.value', index=1,
      number=2, type=11, cpp_type=10, label=1,
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
  serialized_options=_b('8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=238,
  serialized_end=309,
)

_OBSERVATION_EDGEVALUESENTRY = _descriptor.Descriptor(
  name='EdgeValuesEntry',
  full_name='energyplatform.Observation.EdgeValuesEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='energyplatform.Observation.EdgeValuesEntry.key', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='energyplatform.Observation.EdgeValuesEntry.value', index=1,
      number=2, type=11, cpp_type=10, label=1,
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
  serialized_options=_b('8\001'),
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=311,
  serialized_end=382,
)

_OBSERVATION = _descriptor.Descriptor(
  name='Observation',
  full_name='energyplatform.Observation',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='node_values', full_name='energyplatform.Observation.node_values', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='edge_values', full_name='energyplatform.Observation.edge_values', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[_OBSERVATION_NODEVALUESENTRY, _OBSERVATION_EDGEVALUESENTRY, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=91,
  serialized_end=382,
)

_OBSERVATION_NODEVALUESENTRY.fields_by_name['value'].message_type = energyplatform_dot_core_dot_graph__pb2._NODE
_OBSERVATION_NODEVALUESENTRY.containing_type = _OBSERVATION
_OBSERVATION_EDGEVALUESENTRY.fields_by_name['value'].message_type = energyplatform_dot_core_dot_graph__pb2._EDGE
_OBSERVATION_EDGEVALUESENTRY.containing_type = _OBSERVATION
_OBSERVATION.fields_by_name['node_values'].message_type = _OBSERVATION_NODEVALUESENTRY
_OBSERVATION.fields_by_name['edge_values'].message_type = _OBSERVATION_EDGEVALUESENTRY
DESCRIPTOR.message_types_by_name['Observation'] = _OBSERVATION
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Observation = _reflection.GeneratedProtocolMessageType('Observation', (_message.Message,), {

  'NodeValuesEntry' : _reflection.GeneratedProtocolMessageType('NodeValuesEntry', (_message.Message,), {
    'DESCRIPTOR' : _OBSERVATION_NODEVALUESENTRY,
    '__module__' : 'energyplatform.core.observation_pb2'
    # @@protoc_insertion_point(class_scope:energyplatform.Observation.NodeValuesEntry)
    })
  ,

  'EdgeValuesEntry' : _reflection.GeneratedProtocolMessageType('EdgeValuesEntry', (_message.Message,), {
    'DESCRIPTOR' : _OBSERVATION_EDGEVALUESENTRY,
    '__module__' : 'energyplatform.core.observation_pb2'
    # @@protoc_insertion_point(class_scope:energyplatform.Observation.EdgeValuesEntry)
    })
  ,
  'DESCRIPTOR' : _OBSERVATION,
  '__module__' : 'energyplatform.core.observation_pb2'
  # @@protoc_insertion_point(class_scope:energyplatform.Observation)
  })
_sym_db.RegisterMessage(Observation)
_sym_db.RegisterMessage(Observation.NodeValuesEntry)
_sym_db.RegisterMessage(Observation.EdgeValuesEntry)


_OBSERVATION_NODEVALUESENTRY._options = None
_OBSERVATION_EDGEVALUESENTRY._options = None
# @@protoc_insertion_point(module_scope)
