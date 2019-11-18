// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: api/core/predictor_service.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_api_2fcore_2fpredictor_5fservice_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_api_2fcore_2fpredictor_5fservice_2eproto

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
#include "api/core/action.pb.h"
#include "api/core/observation.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_api_2fcore_2fpredictor_5fservice_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_api_2fcore_2fpredictor_5fservice_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_api_2fcore_2fpredictor_5fservice_2eproto;
namespace api {
class PredictReponse;
class PredictReponseDefaultTypeInternal;
extern PredictReponseDefaultTypeInternal _PredictReponse_default_instance_;
class PredictRequest;
class PredictRequestDefaultTypeInternal;
extern PredictRequestDefaultTypeInternal _PredictRequest_default_instance_;
}  // namespace api
PROTOBUF_NAMESPACE_OPEN
template<> ::api::PredictReponse* Arena::CreateMaybeMessage<::api::PredictReponse>(Arena*);
template<> ::api::PredictRequest* Arena::CreateMaybeMessage<::api::PredictRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace api {

// ===================================================================

class PredictRequest :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:api.PredictRequest) */ {
 public:
  PredictRequest();
  virtual ~PredictRequest();

  PredictRequest(const PredictRequest& from);
  PredictRequest(PredictRequest&& from) noexcept
    : PredictRequest() {
    *this = ::std::move(from);
  }

  inline PredictRequest& operator=(const PredictRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline PredictRequest& operator=(PredictRequest&& from) noexcept {
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
  static const PredictRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PredictRequest* internal_default_instance() {
    return reinterpret_cast<const PredictRequest*>(
               &_PredictRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(PredictRequest& a, PredictRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(PredictRequest* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PredictRequest* New() const final {
    return CreateMaybeMessage<PredictRequest>(nullptr);
  }

  PredictRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PredictRequest>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PredictRequest& from);
  void MergeFrom(const PredictRequest& from);
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
  void InternalSwap(PredictRequest* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "api.PredictRequest";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_api_2fcore_2fpredictor_5fservice_2eproto);
    return ::descriptor_table_api_2fcore_2fpredictor_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kObservationFieldNumber = 1,
  };
  // .api.Observation observation = 1;
  bool has_observation() const;
  void clear_observation();
  const ::api::Observation& observation() const;
  ::api::Observation* release_observation();
  ::api::Observation* mutable_observation();
  void set_allocated_observation(::api::Observation* observation);

  // @@protoc_insertion_point(class_scope:api.PredictRequest)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::api::Observation* observation_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_api_2fcore_2fpredictor_5fservice_2eproto;
};
// -------------------------------------------------------------------

class PredictReponse :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:api.PredictReponse) */ {
 public:
  PredictReponse();
  virtual ~PredictReponse();

  PredictReponse(const PredictReponse& from);
  PredictReponse(PredictReponse&& from) noexcept
    : PredictReponse() {
    *this = ::std::move(from);
  }

  inline PredictReponse& operator=(const PredictReponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline PredictReponse& operator=(PredictReponse&& from) noexcept {
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
  static const PredictReponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PredictReponse* internal_default_instance() {
    return reinterpret_cast<const PredictReponse*>(
               &_PredictReponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PredictReponse& a, PredictReponse& b) {
    a.Swap(&b);
  }
  inline void Swap(PredictReponse* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PredictReponse* New() const final {
    return CreateMaybeMessage<PredictReponse>(nullptr);
  }

  PredictReponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PredictReponse>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PredictReponse& from);
  void MergeFrom(const PredictReponse& from);
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
  void InternalSwap(PredictReponse* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "api.PredictReponse";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_api_2fcore_2fpredictor_5fservice_2eproto);
    return ::descriptor_table_api_2fcore_2fpredictor_5fservice_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kActionFieldNumber = 1,
  };
  // .api.Action action = 1;
  bool has_action() const;
  void clear_action();
  const ::api::Action& action() const;
  ::api::Action* release_action();
  ::api::Action* mutable_action();
  void set_allocated_action(::api::Action* action);

  // @@protoc_insertion_point(class_scope:api.PredictReponse)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::api::Action* action_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_api_2fcore_2fpredictor_5fservice_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// PredictRequest

// .api.Observation observation = 1;
inline bool PredictRequest::has_observation() const {
  return this != internal_default_instance() && observation_ != nullptr;
}
inline const ::api::Observation& PredictRequest::observation() const {
  const ::api::Observation* p = observation_;
  // @@protoc_insertion_point(field_get:api.PredictRequest.observation)
  return p != nullptr ? *p : *reinterpret_cast<const ::api::Observation*>(
      &::api::_Observation_default_instance_);
}
inline ::api::Observation* PredictRequest::release_observation() {
  // @@protoc_insertion_point(field_release:api.PredictRequest.observation)
  
  ::api::Observation* temp = observation_;
  observation_ = nullptr;
  return temp;
}
inline ::api::Observation* PredictRequest::mutable_observation() {
  
  if (observation_ == nullptr) {
    auto* p = CreateMaybeMessage<::api::Observation>(GetArenaNoVirtual());
    observation_ = p;
  }
  // @@protoc_insertion_point(field_mutable:api.PredictRequest.observation)
  return observation_;
}
inline void PredictRequest::set_allocated_observation(::api::Observation* observation) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(observation_);
  }
  if (observation) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      observation = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, observation, submessage_arena);
    }
    
  } else {
    
  }
  observation_ = observation;
  // @@protoc_insertion_point(field_set_allocated:api.PredictRequest.observation)
}

// -------------------------------------------------------------------

// PredictReponse

// .api.Action action = 1;
inline bool PredictReponse::has_action() const {
  return this != internal_default_instance() && action_ != nullptr;
}
inline const ::api::Action& PredictReponse::action() const {
  const ::api::Action* p = action_;
  // @@protoc_insertion_point(field_get:api.PredictReponse.action)
  return p != nullptr ? *p : *reinterpret_cast<const ::api::Action*>(
      &::api::_Action_default_instance_);
}
inline ::api::Action* PredictReponse::release_action() {
  // @@protoc_insertion_point(field_release:api.PredictReponse.action)
  
  ::api::Action* temp = action_;
  action_ = nullptr;
  return temp;
}
inline ::api::Action* PredictReponse::mutable_action() {
  
  if (action_ == nullptr) {
    auto* p = CreateMaybeMessage<::api::Action>(GetArenaNoVirtual());
    action_ = p;
  }
  // @@protoc_insertion_point(field_mutable:api.PredictReponse.action)
  return action_;
}
inline void PredictReponse::set_allocated_action(::api::Action* action) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == nullptr) {
    delete reinterpret_cast< ::PROTOBUF_NAMESPACE_ID::MessageLite*>(action_);
  }
  if (action) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena = nullptr;
    if (message_arena != submessage_arena) {
      action = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, action, submessage_arena);
    }
    
  } else {
    
  }
  action_ = action;
  // @@protoc_insertion_point(field_set_allocated:api.PredictReponse.action)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace api

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_api_2fcore_2fpredictor_5fservice_2eproto
