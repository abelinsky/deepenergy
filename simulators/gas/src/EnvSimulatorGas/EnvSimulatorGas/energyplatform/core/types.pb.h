// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/types.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2ftypes_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2ftypes_2eproto

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2ftypes_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_energyplatform_2fcore_2ftypes_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2ftypes_2eproto;
namespace energyplatform {
class ContinuousInterval;
class ContinuousIntervalDefaultTypeInternal;
extern ContinuousIntervalDefaultTypeInternal _ContinuousInterval_default_instance_;
class DiscreteInterval;
class DiscreteIntervalDefaultTypeInternal;
extern DiscreteIntervalDefaultTypeInternal _DiscreteInterval_default_instance_;
class PhysicalParam;
class PhysicalParamDefaultTypeInternal;
extern PhysicalParamDefaultTypeInternal _PhysicalParam_default_instance_;
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> ::energyplatform::ContinuousInterval* Arena::CreateMaybeMessage<::energyplatform::ContinuousInterval>(Arena*);
template<> ::energyplatform::DiscreteInterval* Arena::CreateMaybeMessage<::energyplatform::DiscreteInterval>(Arena*);
template<> ::energyplatform::PhysicalParam* Arena::CreateMaybeMessage<::energyplatform::PhysicalParam>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace energyplatform {

enum ParameterType : int {
  PT_DISCRETE = 0,
  PT_CONTINUOUS = 1,
  ParameterType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ParameterType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ParameterType_IsValid(int value);
constexpr ParameterType ParameterType_MIN = PT_DISCRETE;
constexpr ParameterType ParameterType_MAX = PT_CONTINUOUS;
constexpr int ParameterType_ARRAYSIZE = ParameterType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ParameterType_descriptor();
template<typename T>
inline const std::string& ParameterType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ParameterType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ParameterType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ParameterType_descriptor(), enum_t_value);
}
inline bool ParameterType_Parse(
    const std::string& name, ParameterType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ParameterType>(
    ParameterType_descriptor(), name, value);
}
enum PhysicalValueType : int {
  PV_NOTYPE = 0,
  PV_STATE = 1,
  PV_PRESSURE = 2,
  PV_TEMPERATURE = 3,
  PV_DENSITY = 4,
  PV_VOLUME = 5,
  PV_FREQUENCY = 6,
  PhysicalValueType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  PhysicalValueType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool PhysicalValueType_IsValid(int value);
constexpr PhysicalValueType PhysicalValueType_MIN = PV_NOTYPE;
constexpr PhysicalValueType PhysicalValueType_MAX = PV_FREQUENCY;
constexpr int PhysicalValueType_ARRAYSIZE = PhysicalValueType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PhysicalValueType_descriptor();
template<typename T>
inline const std::string& PhysicalValueType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PhysicalValueType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PhysicalValueType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PhysicalValueType_descriptor(), enum_t_value);
}
inline bool PhysicalValueType_Parse(
    const std::string& name, PhysicalValueType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PhysicalValueType>(
    PhysicalValueType_descriptor(), name, value);
}
// ===================================================================

class DiscreteInterval :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.DiscreteInterval) */ {
 public:
  DiscreteInterval();
  virtual ~DiscreteInterval();

  DiscreteInterval(const DiscreteInterval& from);
  DiscreteInterval(DiscreteInterval&& from) noexcept
    : DiscreteInterval() {
    *this = ::std::move(from);
  }

  inline DiscreteInterval& operator=(const DiscreteInterval& from) {
    CopyFrom(from);
    return *this;
  }
  inline DiscreteInterval& operator=(DiscreteInterval&& from) noexcept {
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
  static const DiscreteInterval& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DiscreteInterval* internal_default_instance() {
    return reinterpret_cast<const DiscreteInterval*>(
               &_DiscreteInterval_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(DiscreteInterval& a, DiscreteInterval& b) {
    a.Swap(&b);
  }
  inline void Swap(DiscreteInterval* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline DiscreteInterval* New() const final {
    return CreateMaybeMessage<DiscreteInterval>(nullptr);
  }

  DiscreteInterval* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<DiscreteInterval>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const DiscreteInterval& from);
  void MergeFrom(const DiscreteInterval& from);
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
  void InternalSwap(DiscreteInterval* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.DiscreteInterval";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2ftypes_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2ftypes_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kNFieldNumber = 1,
  };
  // int32 n = 1;
  void clear_n();
  ::PROTOBUF_NAMESPACE_ID::int32 n() const;
  void set_n(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:energyplatform.DiscreteInterval)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::int32 n_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2ftypes_2eproto;
};
// -------------------------------------------------------------------

class ContinuousInterval :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.ContinuousInterval) */ {
 public:
  ContinuousInterval();
  virtual ~ContinuousInterval();

  ContinuousInterval(const ContinuousInterval& from);
  ContinuousInterval(ContinuousInterval&& from) noexcept
    : ContinuousInterval() {
    *this = ::std::move(from);
  }

  inline ContinuousInterval& operator=(const ContinuousInterval& from) {
    CopyFrom(from);
    return *this;
  }
  inline ContinuousInterval& operator=(ContinuousInterval&& from) noexcept {
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
  static const ContinuousInterval& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ContinuousInterval* internal_default_instance() {
    return reinterpret_cast<const ContinuousInterval*>(
               &_ContinuousInterval_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(ContinuousInterval& a, ContinuousInterval& b) {
    a.Swap(&b);
  }
  inline void Swap(ContinuousInterval* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ContinuousInterval* New() const final {
    return CreateMaybeMessage<ContinuousInterval>(nullptr);
  }

  ContinuousInterval* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ContinuousInterval>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ContinuousInterval& from);
  void MergeFrom(const ContinuousInterval& from);
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
  void InternalSwap(ContinuousInterval* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.ContinuousInterval";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2ftypes_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2ftypes_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLowValueFieldNumber = 1,
    kHighValueFieldNumber = 2,
  };
  // double low_value = 1;
  void clear_low_value();
  double low_value() const;
  void set_low_value(double value);

  // double high_value = 2;
  void clear_high_value();
  double high_value() const;
  void set_high_value(double value);

  // @@protoc_insertion_point(class_scope:energyplatform.ContinuousInterval)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  double low_value_;
  double high_value_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2ftypes_2eproto;
};
// -------------------------------------------------------------------

class PhysicalParam :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:energyplatform.PhysicalParam) */ {
 public:
  PhysicalParam();
  virtual ~PhysicalParam();

  PhysicalParam(const PhysicalParam& from);
  PhysicalParam(PhysicalParam&& from) noexcept
    : PhysicalParam() {
    *this = ::std::move(from);
  }

  inline PhysicalParam& operator=(const PhysicalParam& from) {
    CopyFrom(from);
    return *this;
  }
  inline PhysicalParam& operator=(PhysicalParam&& from) noexcept {
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
  static const PhysicalParam& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const PhysicalParam* internal_default_instance() {
    return reinterpret_cast<const PhysicalParam*>(
               &_PhysicalParam_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(PhysicalParam& a, PhysicalParam& b) {
    a.Swap(&b);
  }
  inline void Swap(PhysicalParam* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline PhysicalParam* New() const final {
    return CreateMaybeMessage<PhysicalParam>(nullptr);
  }

  PhysicalParam* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<PhysicalParam>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const PhysicalParam& from);
  void MergeFrom(const PhysicalParam& from);
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
  void InternalSwap(PhysicalParam* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "energyplatform.PhysicalParam";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_energyplatform_2fcore_2ftypes_2eproto);
    return ::descriptor_table_energyplatform_2fcore_2ftypes_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTypeFieldNumber = 1,
    kValueFieldNumber = 2,
  };
  // .energyplatform.PhysicalValueType type = 1;
  void clear_type();
  ::energyplatform::PhysicalValueType type() const;
  void set_type(::energyplatform::PhysicalValueType value);

  // float value = 2;
  void clear_value();
  float value() const;
  void set_value(float value);

  // @@protoc_insertion_point(class_scope:energyplatform.PhysicalParam)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  int type_;
  float value_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_energyplatform_2fcore_2ftypes_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// DiscreteInterval

// int32 n = 1;
inline void DiscreteInterval::clear_n() {
  n_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 DiscreteInterval::n() const {
  // @@protoc_insertion_point(field_get:energyplatform.DiscreteInterval.n)
  return n_;
}
inline void DiscreteInterval::set_n(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  n_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.DiscreteInterval.n)
}

// -------------------------------------------------------------------

// ContinuousInterval

// double low_value = 1;
inline void ContinuousInterval::clear_low_value() {
  low_value_ = 0;
}
inline double ContinuousInterval::low_value() const {
  // @@protoc_insertion_point(field_get:energyplatform.ContinuousInterval.low_value)
  return low_value_;
}
inline void ContinuousInterval::set_low_value(double value) {
  
  low_value_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.ContinuousInterval.low_value)
}

// double high_value = 2;
inline void ContinuousInterval::clear_high_value() {
  high_value_ = 0;
}
inline double ContinuousInterval::high_value() const {
  // @@protoc_insertion_point(field_get:energyplatform.ContinuousInterval.high_value)
  return high_value_;
}
inline void ContinuousInterval::set_high_value(double value) {
  
  high_value_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.ContinuousInterval.high_value)
}

// -------------------------------------------------------------------

// PhysicalParam

// .energyplatform.PhysicalValueType type = 1;
inline void PhysicalParam::clear_type() {
  type_ = 0;
}
inline ::energyplatform::PhysicalValueType PhysicalParam::type() const {
  // @@protoc_insertion_point(field_get:energyplatform.PhysicalParam.type)
  return static_cast< ::energyplatform::PhysicalValueType >(type_);
}
inline void PhysicalParam::set_type(::energyplatform::PhysicalValueType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.PhysicalParam.type)
}

// float value = 2;
inline void PhysicalParam::clear_value() {
  value_ = 0;
}
inline float PhysicalParam::value() const {
  // @@protoc_insertion_point(field_get:energyplatform.PhysicalParam.value)
  return value_;
}
inline void PhysicalParam::set_value(float value) {
  
  value_ = value;
  // @@protoc_insertion_point(field_set:energyplatform.PhysicalParam.value)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace energyplatform

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::energyplatform::ParameterType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::energyplatform::ParameterType>() {
  return ::energyplatform::ParameterType_descriptor();
}
template <> struct is_proto_enum< ::energyplatform::PhysicalValueType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::energyplatform::PhysicalValueType>() {
  return ::energyplatform::PhysicalValueType_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_energyplatform_2fcore_2ftypes_2eproto
