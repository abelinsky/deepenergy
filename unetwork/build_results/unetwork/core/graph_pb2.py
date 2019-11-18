# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: unetwork/core/graph.proto

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
  name='unetwork/core/graph.proto',
  package='unetwork',
  syntax='proto3',
  serialized_options=None,
  serialized_pb=_b('\n\x19unetwork/core/graph.proto\x12\x08unetwork\x1a\x19unetwork/core/types.proto\";\n\x04Node\x12\x0b\n\x03uid\x18\x01 \x01(\x05\x12&\n\x05param\x18\x02 \x03(\x0b\x32\x17.unetwork.PhysicalParam\"A\n\x04\x45\x64ge\x12\x0b\n\x03uid\x18\x01 \x01(\x05\x12,\n\x0b\x65\x64ge_params\x18\x02 \x03(\x0b\x32\x17.unetwork.PhysicalParam\"\xd9\x01\n\x05Graph\x12)\n\x05nodes\x18\x01 \x03(\x0b\x32\x1a.unetwork.Graph.NodesEntry\x12)\n\x05\x65\x64ges\x18\x02 \x03(\x0b\x32\x1a.unetwork.Graph.EdgesEntry\x1a<\n\nNodesEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12\x1d\n\x05value\x18\x02 \x01(\x0b\x32\x0e.unetwork.Node:\x02\x38\x01\x1a<\n\nEdgesEntry\x12\x0b\n\x03key\x18\x01 \x01(\x05\x12\x1d\n\x05value\x18\x02 \x01(\x0b\x32\x0e.unetwork.Edge:\x02\x38\x01\x62\x06proto3')
  ,
  dependencies=[unetwork_dot_core_dot_types__pb2.DESCRIPTOR,])




_NODE = _descriptor.Descriptor(
  name='Node',
  full_name='unetwork.Node',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='uid', full_name='unetwork.Node.uid', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='param', full_name='unetwork.Node.param', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=66,
  serialized_end=125,
)


_EDGE = _descriptor.Descriptor(
  name='Edge',
  full_name='unetwork.Edge',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='uid', full_name='unetwork.Edge.uid', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='edge_params', full_name='unetwork.Edge.edge_params', index=1,
      number=2, type=11, cpp_type=10, label=3,
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
  serialized_start=127,
  serialized_end=192,
)


_GRAPH_NODESENTRY = _descriptor.Descriptor(
  name='NodesEntry',
  full_name='unetwork.Graph.NodesEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='unetwork.Graph.NodesEntry.key', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='unetwork.Graph.NodesEntry.value', index=1,
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
  serialized_start=290,
  serialized_end=350,
)

_GRAPH_EDGESENTRY = _descriptor.Descriptor(
  name='EdgesEntry',
  full_name='unetwork.Graph.EdgesEntry',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='unetwork.Graph.EdgesEntry.key', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='value', full_name='unetwork.Graph.EdgesEntry.value', index=1,
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
  serialized_start=352,
  serialized_end=412,
)

_GRAPH = _descriptor.Descriptor(
  name='Graph',
  full_name='unetwork.Graph',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='nodes', full_name='unetwork.Graph.nodes', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='edges', full_name='unetwork.Graph.edges', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      serialized_options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[_GRAPH_NODESENTRY, _GRAPH_EDGESENTRY, ],
  enum_types=[
  ],
  serialized_options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=195,
  serialized_end=412,
)

_NODE.fields_by_name['param'].message_type = unetwork_dot_core_dot_types__pb2._PHYSICALPARAM
_EDGE.fields_by_name['edge_params'].message_type = unetwork_dot_core_dot_types__pb2._PHYSICALPARAM
_GRAPH_NODESENTRY.fields_by_name['value'].message_type = _NODE
_GRAPH_NODESENTRY.containing_type = _GRAPH
_GRAPH_EDGESENTRY.fields_by_name['value'].message_type = _EDGE
_GRAPH_EDGESENTRY.containing_type = _GRAPH
_GRAPH.fields_by_name['nodes'].message_type = _GRAPH_NODESENTRY
_GRAPH.fields_by_name['edges'].message_type = _GRAPH_EDGESENTRY
DESCRIPTOR.message_types_by_name['Node'] = _NODE
DESCRIPTOR.message_types_by_name['Edge'] = _EDGE
DESCRIPTOR.message_types_by_name['Graph'] = _GRAPH
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Node = _reflection.GeneratedProtocolMessageType('Node', (_message.Message,), {
  'DESCRIPTOR' : _NODE,
  '__module__' : 'unetwork.core.graph_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.Node)
  })
_sym_db.RegisterMessage(Node)

Edge = _reflection.GeneratedProtocolMessageType('Edge', (_message.Message,), {
  'DESCRIPTOR' : _EDGE,
  '__module__' : 'unetwork.core.graph_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.Edge)
  })
_sym_db.RegisterMessage(Edge)

Graph = _reflection.GeneratedProtocolMessageType('Graph', (_message.Message,), {

  'NodesEntry' : _reflection.GeneratedProtocolMessageType('NodesEntry', (_message.Message,), {
    'DESCRIPTOR' : _GRAPH_NODESENTRY,
    '__module__' : 'unetwork.core.graph_pb2'
    # @@protoc_insertion_point(class_scope:unetwork.Graph.NodesEntry)
    })
  ,

  'EdgesEntry' : _reflection.GeneratedProtocolMessageType('EdgesEntry', (_message.Message,), {
    'DESCRIPTOR' : _GRAPH_EDGESENTRY,
    '__module__' : 'unetwork.core.graph_pb2'
    # @@protoc_insertion_point(class_scope:unetwork.Graph.EdgesEntry)
    })
  ,
  'DESCRIPTOR' : _GRAPH,
  '__module__' : 'unetwork.core.graph_pb2'
  # @@protoc_insertion_point(class_scope:unetwork.Graph)
  })
_sym_db.RegisterMessage(Graph)
_sym_db.RegisterMessage(Graph.NodesEntry)
_sym_db.RegisterMessage(Graph.EdgesEntry)


_GRAPH_NODESENTRY._options = None
_GRAPH_EDGESENTRY._options = None
# @@protoc_insertion_point(module_scope)
