#include "pch.h"
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/predictor_service.proto

#include "energyplatform/core/predictor_service.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2faction_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Action_energyplatform_2fcore_2faction_2eproto;
extern PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2fobservation_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto;
namespace energyplatform {
class PredictRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<PredictRequest> _instance;
} _PredictRequest_default_instance_;
class PredictReponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<PredictReponse> _instance;
} _PredictReponse_default_instance_;
}  // namespace energyplatform
static void InitDefaultsscc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::energyplatform::_PredictReponse_default_instance_;
    new (ptr) ::energyplatform::PredictReponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::energyplatform::PredictReponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto}, {
      &scc_info_Action_energyplatform_2fcore_2faction_2eproto.base,}};

static void InitDefaultsscc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::energyplatform::_PredictRequest_default_instance_;
    new (ptr) ::energyplatform::PredictRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::energyplatform::PredictRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto}, {
      &scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_energyplatform_2fcore_2fpredictor_5fservice_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_energyplatform_2fcore_2fpredictor_5fservice_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_energyplatform_2fcore_2fpredictor_5fservice_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_energyplatform_2fcore_2fpredictor_5fservice_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::energyplatform::PredictRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::energyplatform::PredictRequest, observation_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::energyplatform::PredictReponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::energyplatform::PredictReponse, action_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::energyplatform::PredictRequest)},
  { 6, -1, sizeof(::energyplatform::PredictReponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::energyplatform::_PredictRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::energyplatform::_PredictReponse_default_instance_),
};

const char descriptor_table_protodef_energyplatform_2fcore_2fpredictor_5fservice_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n+energyplatform/core/predictor_service."
  "proto\022\016energyplatform\032 energyplatform/co"
  "re/action.proto\032%energyplatform/core/obs"
  "ervation.proto\"B\n\016PredictRequest\0220\n\013obse"
  "rvation\030\001 \001(\0132\033.energyplatform.Observati"
  "on\"8\n\016PredictReponse\022&\n\006action\030\001 \001(\0132\026.e"
  "nergyplatform.Action2]\n\020PredictorService"
  "\022I\n\007Predict\022\036.energyplatform.PredictRequ"
  "est\032\036.energyplatform.PredictReponseb\006pro"
  "to3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_deps[2] = {
  &::descriptor_table_energyplatform_2fcore_2faction_2eproto,
  &::descriptor_table_energyplatform_2fcore_2fobservation_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_sccs[2] = {
  &scc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base,
  &scc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_once;
static bool descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto = {
  &descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_initialized, descriptor_table_protodef_energyplatform_2fcore_2fpredictor_5fservice_2eproto, "energyplatform/core/predictor_service.proto", 363,
  &descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_once, descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_sccs, descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto_deps, 2, 2,
  schemas, file_default_instances, TableStruct_energyplatform_2fcore_2fpredictor_5fservice_2eproto::offsets,
  file_level_metadata_energyplatform_2fcore_2fpredictor_5fservice_2eproto, 2, file_level_enum_descriptors_energyplatform_2fcore_2fpredictor_5fservice_2eproto, file_level_service_descriptors_energyplatform_2fcore_2fpredictor_5fservice_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_energyplatform_2fcore_2fpredictor_5fservice_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_energyplatform_2fcore_2fpredictor_5fservice_2eproto), true);
namespace energyplatform {

// ===================================================================

void PredictRequest::InitAsDefaultInstance() {
  ::energyplatform::_PredictRequest_default_instance_._instance.get_mutable()->observation_ = const_cast< ::energyplatform::Observation*>(
      ::energyplatform::Observation::internal_default_instance());
}
class PredictRequest::_Internal {
 public:
  static const ::energyplatform::Observation& observation(const PredictRequest* msg);
};

const ::energyplatform::Observation&
PredictRequest::_Internal::observation(const PredictRequest* msg) {
  return *msg->observation_;
}
void PredictRequest::clear_observation() {
  if (GetArenaNoVirtual() == nullptr && observation_ != nullptr) {
    delete observation_;
  }
  observation_ = nullptr;
}
PredictRequest::PredictRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:energyplatform.PredictRequest)
}
PredictRequest::PredictRequest(const PredictRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_observation()) {
    observation_ = new ::energyplatform::Observation(*from.observation_);
  } else {
    observation_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:energyplatform.PredictRequest)
}

void PredictRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base);
  observation_ = nullptr;
}

PredictRequest::~PredictRequest() {
  // @@protoc_insertion_point(destructor:energyplatform.PredictRequest)
  SharedDtor();
}

void PredictRequest::SharedDtor() {
  if (this != internal_default_instance()) delete observation_;
}

void PredictRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const PredictRequest& PredictRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_PredictRequest_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base);
  return *internal_default_instance();
}


void PredictRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:energyplatform.PredictRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == nullptr && observation_ != nullptr) {
    delete observation_;
  }
  observation_ = nullptr;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* PredictRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .energyplatform.Observation observation = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(mutable_observation(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool PredictRequest::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:energyplatform.PredictRequest)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .energyplatform.Observation observation = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
               input, mutable_observation()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:energyplatform.PredictRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:energyplatform.PredictRequest)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void PredictRequest::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:energyplatform.PredictRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .energyplatform.Observation observation = 1;
  if (this->has_observation()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, _Internal::observation(this), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:energyplatform.PredictRequest)
}

::PROTOBUF_NAMESPACE_ID::uint8* PredictRequest::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:energyplatform.PredictRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .energyplatform.Observation observation = 1;
  if (this->has_observation()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, _Internal::observation(this), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:energyplatform.PredictRequest)
  return target;
}

size_t PredictRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:energyplatform.PredictRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .energyplatform.Observation observation = 1;
  if (this->has_observation()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *observation_);
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PredictRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:energyplatform.PredictRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const PredictRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<PredictRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:energyplatform.PredictRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:energyplatform.PredictRequest)
    MergeFrom(*source);
  }
}

void PredictRequest::MergeFrom(const PredictRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:energyplatform.PredictRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_observation()) {
    mutable_observation()->::energyplatform::Observation::MergeFrom(from.observation());
  }
}

void PredictRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:energyplatform.PredictRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PredictRequest::CopyFrom(const PredictRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:energyplatform.PredictRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PredictRequest::IsInitialized() const {
  return true;
}

void PredictRequest::InternalSwap(PredictRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(observation_, other->observation_);
}

::PROTOBUF_NAMESPACE_ID::Metadata PredictRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void PredictReponse::InitAsDefaultInstance() {
  ::energyplatform::_PredictReponse_default_instance_._instance.get_mutable()->action_ = const_cast< ::energyplatform::Action*>(
      ::energyplatform::Action::internal_default_instance());
}
class PredictReponse::_Internal {
 public:
  static const ::energyplatform::Action& action(const PredictReponse* msg);
};

const ::energyplatform::Action&
PredictReponse::_Internal::action(const PredictReponse* msg) {
  return *msg->action_;
}
void PredictReponse::clear_action() {
  if (GetArenaNoVirtual() == nullptr && action_ != nullptr) {
    delete action_;
  }
  action_ = nullptr;
}
PredictReponse::PredictReponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:energyplatform.PredictReponse)
}
PredictReponse::PredictReponse(const PredictReponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_action()) {
    action_ = new ::energyplatform::Action(*from.action_);
  } else {
    action_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:energyplatform.PredictReponse)
}

void PredictReponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base);
  action_ = nullptr;
}

PredictReponse::~PredictReponse() {
  // @@protoc_insertion_point(destructor:energyplatform.PredictReponse)
  SharedDtor();
}

void PredictReponse::SharedDtor() {
  if (this != internal_default_instance()) delete action_;
}

void PredictReponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const PredictReponse& PredictReponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_PredictReponse_energyplatform_2fcore_2fpredictor_5fservice_2eproto.base);
  return *internal_default_instance();
}


void PredictReponse::Clear() {
// @@protoc_insertion_point(message_clear_start:energyplatform.PredictReponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == nullptr && action_ != nullptr) {
    delete action_;
  }
  action_ = nullptr;
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* PredictReponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .energyplatform.Action action = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(mutable_action(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool PredictReponse::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:energyplatform.PredictReponse)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .energyplatform.Action action = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
               input, mutable_action()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:energyplatform.PredictReponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:energyplatform.PredictReponse)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void PredictReponse::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:energyplatform.PredictReponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .energyplatform.Action action = 1;
  if (this->has_action()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, _Internal::action(this), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:energyplatform.PredictReponse)
}

::PROTOBUF_NAMESPACE_ID::uint8* PredictReponse::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:energyplatform.PredictReponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .energyplatform.Action action = 1;
  if (this->has_action()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, _Internal::action(this), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:energyplatform.PredictReponse)
  return target;
}

size_t PredictReponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:energyplatform.PredictReponse)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .energyplatform.Action action = 1;
  if (this->has_action()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *action_);
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PredictReponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:energyplatform.PredictReponse)
  GOOGLE_DCHECK_NE(&from, this);
  const PredictReponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<PredictReponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:energyplatform.PredictReponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:energyplatform.PredictReponse)
    MergeFrom(*source);
  }
}

void PredictReponse::MergeFrom(const PredictReponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:energyplatform.PredictReponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_action()) {
    mutable_action()->::energyplatform::Action::MergeFrom(from.action());
  }
}

void PredictReponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:energyplatform.PredictReponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PredictReponse::CopyFrom(const PredictReponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:energyplatform.PredictReponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PredictReponse::IsInitialized() const {
  return true;
}

void PredictReponse::InternalSwap(PredictReponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(action_, other->action_);
}

::PROTOBUF_NAMESPACE_ID::Metadata PredictReponse::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::energyplatform::PredictRequest* Arena::CreateMaybeMessage< ::energyplatform::PredictRequest >(Arena* arena) {
  return Arena::CreateInternal< ::energyplatform::PredictRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::energyplatform::PredictReponse* Arena::CreateMaybeMessage< ::energyplatform::PredictReponse >(Arena* arena) {
  return Arena::CreateInternal< ::energyplatform::PredictReponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
