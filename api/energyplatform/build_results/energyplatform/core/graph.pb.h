// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/graph.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2fgraph_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2fgraph_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/map.h>  // IWYU pragma: export
#include <google/protobuf/map_entry.h>
#include <google/protobuf/map_field_inl.h>
#include <google/protobuf/unknown_field_set.h>
#include "energyplatform/core/types.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2fgraph_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_energyplatform_2fcore_2fgraph_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[5]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2fgraph_2eproto;
namespace energyplatform {
class Edge;
class EdgeDefaultTypeInternal;
extern EdgeDefaultTypeInternal _Edge_default_instance_;
class Graph;
class GraphDefaultTypeInternal;
extern GraphDefaultTypeInternal _Graph_default_instance_;
class Graph_EdgesEntry_DoNotUse;
class Graph_EdgesEntry_DoNotUseDefaultTypeInternal;
extern Graph_EdgesEntry_DoNotUseDefaultTypeInternal _Graph_EdgesEntry_DoNotUse_default_instance_;
class Graph_NodesEntry_DoNotUse;
class Graph_NodesEntry_DoNotUseDefaultTypeInternal;
extern Graph_NodesEntry_DoNotUseDefaultTypeInternal _Graph_NodesEntry_DoNotUse_default_instance_;
class Node;
class NodeDefaultTypeInternal;
extern NodeDefaultTypeInternal _Node_default_instance_;
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> ::energyplatform::Edge* Arena::CreateMaybeMessage<::energyplatform::Edge>(Arena*);
template<> ::energyplatform::Graph* Arena::CreateMaybeMessage<::energyplatform::Graph>(Arena*);
template<> ::energyplatform::Graph_EdgesEntry_DoNotUse* Arena::CreateMaybeMessage<::energyplatform::Graph_EdgesEntry_DoNotUse>(Arena*);
template<> ::energyplatform::Graph_NodesEntry_DoNotUse* Arena::CreateMaybeMessage<::energyplatform::Graph_NodesEntry_DoNotUse>(Arena*);
template<> ::energyplatform::Node* Arena::CreateMaybeMessage<::energyplatform::Node>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace energyplatform {

// ===================================================================

class Node :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.Node) */ {
 public:
  Node();
  virtual ~Node();

  Node(const Node& from);
  Node(Node&& from) noexcept
    : Node() {
    *this = ::std::move(from);
  }

  inline Node& operator=(const Node& from) {
    CopyFrom(from);
    return *this;
  }
  inline Node& operator=(Node&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Node& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Node* internal_default_instance() {
    return reinterpret_cast<const Node*>(
               &_Node_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Node& a, Node& b) {
    a.Swap(&b);
  }
  inline void Swap(Node* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Node* New() const final {
    return CreateMaybeMessage<Node>(nullptr);
  }

  Node* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Node>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Node& from);
  void MergeFrom(const Node& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Node* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.Node";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2fgraph_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2fgraph_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kParamFieldNumber = 2,
    kUidFieldNumber = 1,
  };
  // repeated .energyplatform.PhysicalParam param = 2;
  int param_size() const;
  void clear_param();
  ::energyplatform::PhysicalParam* mutable_param(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >*
      mutable_param();
  const ::energyplatform::PhysicalParam& param(int index) const;
  ::energyplatform::PhysicalParam* add_param();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >&
      param() const;

  // int32 uid = 1;
  void clear_uid();
  ::PROTOBUF_NAMESPACE_ID::int32 uid() const;
  void set_uid(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:energyplatform.Node)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam > param_;
  ::PROTOBUF_NAMESPACE_ID::int32 uid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2fgraph_2eproto;
};
// -------------------------------------------------------------------

class Edge :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.Edge) */ {
 public:
  Edge();
  virtual ~Edge();

  Edge(const Edge& from);
  Edge(Edge&& from) noexcept
    : Edge() {
    *this = ::std::move(from);
  }

  inline Edge& operator=(const Edge& from) {
    CopyFrom(from);
    return *this;
  }
  inline Edge& operator=(Edge&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Edge& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Edge* internal_default_instance() {
    return reinterpret_cast<const Edge*>(
               &_Edge_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Edge& a, Edge& b) {
    a.Swap(&b);
  }
  inline void Swap(Edge* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Edge* New() const final {
    return CreateMaybeMessage<Edge>(nullptr);
  }

  Edge* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Edge>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Edge& from);
  void MergeFrom(const Edge& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Edge* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.Edge";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2fgraph_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2fgraph_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEdgeParamsFieldNumber = 2,
    kUidFieldNumber = 1,
  };
  // repeated .energyplatform.PhysicalParam edge_params = 2;
  int edge_params_size() const;
  void clear_edge_params();
  ::energyplatform::PhysicalParam* mutable_edge_params(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >*
      mutable_edge_params();
  const ::energyplatform::PhysicalParam& edge_params(int index) const;
  ::energyplatform::PhysicalParam* add_edge_params();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >&
      edge_params() const;

  // int32 uid = 1;
  void clear_uid();
  ::PROTOBUF_NAMESPACE_ID::int32 uid() const;
  void set_uid(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:energyplatform.Edge)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam > edge_params_;
  ::PROTOBUF_NAMESPACE_ID::int32 uid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2fgraph_2eproto;
};
// -------------------------------------------------------------------

class Graph_NodesEntry_DoNotUse : public ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Graph_NodesEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Graph_NodesEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  Graph_NodesEntry_DoNotUse();
  Graph_NodesEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void MergeFrom(const Graph_NodesEntry_DoNotUse& other);
  static const Graph_NodesEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const Graph_NodesEntry_DoNotUse*>(&_Graph_NodesEntry_DoNotUse_default_instance_); }
  static bool ValidateKey(void*) { return true; }
  static bool ValidateValue(void*) { return true; }
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& other) final;
  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2fgraph_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2fgraph_2eproto.file_level_metadata[2];
  }

  public:
};

// -------------------------------------------------------------------

class Graph_EdgesEntry_DoNotUse : public ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Graph_EdgesEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
    0 > {
public:
  typedef ::PROTOBUF_NAMESPACE_ID::internal::MapEntry<Graph_EdgesEntry_DoNotUse, 
    ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
    0 > SuperType;
  Graph_EdgesEntry_DoNotUse();
  Graph_EdgesEntry_DoNotUse(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void MergeFrom(const Graph_EdgesEntry_DoNotUse& other);
  static const Graph_EdgesEntry_DoNotUse* internal_default_instance() { return reinterpret_cast<const Graph_EdgesEntry_DoNotUse*>(&_Graph_EdgesEntry_DoNotUse_default_instance_); }
  static bool ValidateKey(void*) { return true; }
  static bool ValidateValue(void*) { return true; }
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& other) final;
  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2fgraph_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2fgraph_2eproto.file_level_metadata[3];
  }

  public:
};

// -------------------------------------------------------------------

class Graph :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.Graph) */ {
 public:
  Graph();
  virtual ~Graph();

  Graph(const Graph& from);
  Graph(Graph&& from) noexcept
    : Graph() {
    *this = ::std::move(from);
  }

  inline Graph& operator=(const Graph& from) {
    CopyFrom(from);
    return *this;
  }
  inline Graph& operator=(Graph&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Graph& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Graph* internal_default_instance() {
    return reinterpret_cast<const Graph*>(
               &_Graph_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    4;

  friend void swap(Graph& a, Graph& b) {
    a.Swap(&b);
  }
  inline void Swap(Graph* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Graph* New() const final {
    return CreateMaybeMessage<Graph>(nullptr);
  }

  Graph* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Graph>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Graph& from);
  void MergeFrom(const Graph& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Graph* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.Graph";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2fgraph_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2fgraph_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------


  // accessors -------------------------------------------------------

  enum : int {
    kNodesFieldNumber = 1,
    kEdgesFieldNumber = 2,
  };
  // map<int32, .energyplatform.Node> nodes = 1;
  int nodes_size() const;
  void clear_nodes();
  const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node >&
      nodes() const;
  ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node >*
      mutable_nodes();

  // map<int32, .energyplatform.Edge> edges = 2;
  int edges_size() const;
  void clear_edges();
  const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge >&
      edges() const;
  ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge >*
      mutable_edges();

  // @@protoc_insertion_point(class_scope:energyplatform.Graph)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::MapField<
      Graph_NodesEntry_DoNotUse,
      ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
      0 > nodes_;
  ::PROTOBUF_NAMESPACE_ID::internal::MapField<
      Graph_EdgesEntry_DoNotUse,
      ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32,
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_MESSAGE,
      0 > edges_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2fgraph_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Node

// int32 uid = 1;
inline void Node::clear_uid() {
  uid_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Node::uid() const {
  // @@protoc_insertion_point(field_get:energyplatform.Node.uid)
  return uid_;
}
inline void Node::set_uid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  uid_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.Node.uid)
}

// repeated .energyplatform.PhysicalParam param = 2;
inline int Node::param_size() const {
  return param_.size();
}
inline ::energyplatform::PhysicalParam* Node::mutable_param(int index) {
  // @@protoc_insertion_point(field_mutable:energyplatform.Node.param)
  return param_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >*
Node::mutable_param() {
  // @@protoc_insertion_point(field_mutable_list:energyplatform.Node.param)
  return &param_;
}
inline const ::energyplatform::PhysicalParam& Node::param(int index) const {
  // @@protoc_insertion_point(field_get:energyplatform.Node.param)
  return param_.Get(index);
}
inline ::energyplatform::PhysicalParam* Node::add_param() {
  // @@protoc_insertion_point(field_add:energyplatform.Node.param)
  return param_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >&
Node::param() const {
  // @@protoc_insertion_point(field_list:energyplatform.Node.param)
  return param_;
}

// -------------------------------------------------------------------

// Edge

// int32 uid = 1;
inline void Edge::clear_uid() {
  uid_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Edge::uid() const {
  // @@protoc_insertion_point(field_get:energyplatform.Edge.uid)
  return uid_;
}
inline void Edge::set_uid(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  uid_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.Edge.uid)
}

// repeated .energyplatform.PhysicalParam edge_params = 2;
inline int Edge::edge_params_size() const {
  return edge_params_.size();
}
inline ::energyplatform::PhysicalParam* Edge::mutable_edge_params(int index) {
  // @@protoc_insertion_point(field_mutable:energyplatform.Edge.edge_params)
  return edge_params_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >*
Edge::mutable_edge_params() {
  // @@protoc_insertion_point(field_mutable_list:energyplatform.Edge.edge_params)
  return &edge_params_;
}
inline const ::energyplatform::PhysicalParam& Edge::edge_params(int index) const {
  // @@protoc_insertion_point(field_get:energyplatform.Edge.edge_params)
  return edge_params_.Get(index);
}
inline ::energyplatform::PhysicalParam* Edge::add_edge_params() {
  // @@protoc_insertion_point(field_add:energyplatform.Edge.edge_params)
  return edge_params_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::PhysicalParam >&
Edge::edge_params() const {
  // @@protoc_insertion_point(field_list:energyplatform.Edge.edge_params)
  return edge_params_;
}

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// Graph

// map<int32, .energyplatform.Node> nodes = 1;
inline int Graph::nodes_size() const {
  return nodes_.size();
}
inline void Graph::clear_nodes() {
  nodes_.Clear();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node >&
Graph::nodes() const {
  // @@protoc_insertion_point(field_map:energyplatform.Graph.nodes)
  return nodes_.GetMap();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Node >*
Graph::mutable_nodes() {
  // @@protoc_insertion_point(field_mutable_map:energyplatform.Graph.nodes)
  return nodes_.MutableMap();
}

// map<int32, .energyplatform.Edge> edges = 2;
inline int Graph::edges_size() const {
  return edges_.size();
}
inline void Graph::clear_edges() {
  edges_.Clear();
}
inline const ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge >&
Graph::edges() const {
  // @@protoc_insertion_point(field_map:energyplatform.Graph.edges)
  return edges_.GetMap();
}
inline ::PROTOBUF_NAMESPACE_ID::Map< ::PROTOBUF_NAMESPACE_ID::int32, ::energyplatform::Edge >*
Graph::mutable_edges() {
  // @@protoc_insertion_point(field_mutable_map:energyplatform.Graph.edges)
  return edges_.MutableMap();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace energyplatform

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2fgraph_2eproto
