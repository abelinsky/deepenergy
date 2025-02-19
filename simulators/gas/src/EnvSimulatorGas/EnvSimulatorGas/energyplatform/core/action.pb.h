// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/action.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2faction_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2faction_2eproto

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
#include <google/protobuf/unknown_field_set.h>
#include "energyplatform/core/optimization_param.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2faction_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_energyplatform_2fcore_2faction_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2faction_2eproto;
namespace energyplatform {
class Action;
class ActionDefaultTypeInternal;
extern ActionDefaultTypeInternal _Action_default_instance_;
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> ::energyplatform::Action* Arena::CreateMaybeMessage<::energyplatform::Action>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace energyplatform {

// ===================================================================

class Action :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.Action) */ {
 public:
  Action();
  virtual ~Action();

  Action(const Action& from);
  Action(Action&& from) noexcept
    : Action() {
    *this = ::std::move(from);
  }

  inline Action& operator=(const Action& from) {
    CopyFrom(from);
    return *this;
  }
  inline Action& operator=(Action&& from) noexcept {
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
  static const Action& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Action* internal_default_instance() {
    return reinterpret_cast<const Action*>(
               &_Action_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Action& a, Action& b) {
    a.Swap(&b);
  }
  inline void Swap(Action* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Action* New() const final {
    return CreateMaybeMessage<Action>(nullptr);
  }

  Action* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Action>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Action& from);
  void MergeFrom(const Action& from);
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
  void InternalSwap(Action* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.Action";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2faction_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2faction_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOptimizationParamsFieldNumber = 1,
    kInfoFieldNumber = 2,
  };
  // repeated .energyplatform.OptimizationParameter optimization_params = 1;
  int optimization_params_size() const;
  void clear_optimization_params();
  ::energyplatform::OptimizationParameter* mutable_optimization_params(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::OptimizationParameter >*
      mutable_optimization_params();
  const ::energyplatform::OptimizationParameter& optimization_params(int index) const;
  ::energyplatform::OptimizationParameter* add_optimization_params();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::OptimizationParameter >&
      optimization_params() const;

  // string info = 2;
  void clear_info();
  const std::string& info() const;
  void set_info(const std::string& value);
  void set_info(std::string&& value);
  void set_info(const char* value);
  void set_info(const char* value, size_t size);
  std::string* mutable_info();
  std::string* release_info();
  void set_allocated_info(std::string* info);

  // @@protoc_insertion_point(class_scope:energyplatform.Action)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::OptimizationParameter > optimization_params_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr info_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2faction_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Action

// repeated .energyplatform.OptimizationParameter optimization_params = 1;
inline int Action::optimization_params_size() const {
  return optimization_params_.size();
}
inline ::energyplatform::OptimizationParameter* Action::mutable_optimization_params(int index) {
  // @@protoc_insertion_point(field_mutable:energyplatform.Action.optimization_params)
  return optimization_params_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::OptimizationParameter >*
Action::mutable_optimization_params() {
  // @@protoc_insertion_point(field_mutable_list:energyplatform.Action.optimization_params)
  return &optimization_params_;
}
inline const ::energyplatform::OptimizationParameter& Action::optimization_params(int index) const {
  // @@protoc_insertion_point(field_get:energyplatform.Action.optimization_params)
  return optimization_params_.Get(index);
}
inline ::energyplatform::OptimizationParameter* Action::add_optimization_params() {
  // @@protoc_insertion_point(field_add:energyplatform.Action.optimization_params)
  return optimization_params_.Add();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::energyplatform::OptimizationParameter >&
Action::optimization_params() const {
  // @@protoc_insertion_point(field_list:energyplatform.Action.optimization_params)
  return optimization_params_;
}

// string info = 2;
inline void Action::clear_info() {
  info_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Action::info() const {
  // @@protoc_insertion_point(field_get:energyplatform.Action.info)
  return info_.GetNoArena();
}
inline void Action::set_info(const std::string& value) {
  
  info_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:energyplatform.Action.info)
}
inline void Action::set_info(std::string&& value) {
  
  info_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:energyplatform.Action.info)
}
inline void Action::set_info(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  info_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:energyplatform.Action.info)
}
inline void Action::set_info(const char* value, size_t size) {
  
  info_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:energyplatform.Action.info)
}
inline std::string* Action::mutable_info() {
  
  // @@protoc_insertion_point(field_mutable:energyplatform.Action.info)
  return info_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Action::release_info() {
  // @@protoc_insertion_point(field_release:energyplatform.Action.info)
  
  return info_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Action::set_allocated_info(std::string* info) {
  if (info != nullptr) {
    
  } else {
    
  }
  info_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), info);
  // @@protoc_insertion_point(field_set_allocated:energyplatform.Action.info)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace energyplatform

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2faction_2eproto
