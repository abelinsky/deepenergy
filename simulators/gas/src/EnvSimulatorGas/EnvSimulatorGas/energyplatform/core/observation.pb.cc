#include "pch.h"
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/observation.proto

#include "energyplatform/core/observation.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2ftypes_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_PhysicalParam_energyplatform_2fcore_2ftypes_2eproto;
namespace energyplatform {
class ObservationDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Observation> _instance;
} _Observation_default_instance_;
}  // namespace energyplatform
static void InitDefaultsscc_info_Observation_energyplatform_2fcore_2fobservation_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::energyplatform::_Observation_default_instance_;
    new (ptr) ::energyplatform::Observation();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::energyplatform::Observation::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_Observation_energyplatform_2fcore_2fobservation_2eproto}, {
      &scc_info_PhysicalParam_energyplatform_2fcore_2ftypes_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_energyplatform_2fcore_2fobservation_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_energyplatform_2fcore_2fobservation_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_energyplatform_2fcore_2fobservation_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_energyplatform_2fcore_2fobservation_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::energyplatform::Observation, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::energyplatform::Observation, items_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::energyplatform::Observation)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::energyplatform::_Observation_default_instance_),
};

const char descriptor_table_protodef_energyplatform_2fcore_2fobservation_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n%energyplatform/core/observation.proto\022"
  "\016energyplatform\032\037energyplatform/core/typ"
  "es.proto\";\n\013Observation\022,\n\005items\030\001 \003(\0132\035"
  ".energyplatform.PhysicalParamb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_energyplatform_2fcore_2fobservation_2eproto_deps[1] = {
  &::descriptor_table_energyplatform_2fcore_2ftypes_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_energyplatform_2fcore_2fobservation_2eproto_sccs[1] = {
  &scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_energyplatform_2fcore_2fobservation_2eproto_once;
static bool descriptor_table_energyplatform_2fcore_2fobservation_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2fobservation_2eproto = {
  &descriptor_table_energyplatform_2fcore_2fobservation_2eproto_initialized, descriptor_table_protodef_energyplatform_2fcore_2fobservation_2eproto, "energyplatform/core/observation.proto", 157,
  &descriptor_table_energyplatform_2fcore_2fobservation_2eproto_once, descriptor_table_energyplatform_2fcore_2fobservation_2eproto_sccs, descriptor_table_energyplatform_2fcore_2fobservation_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_energyplatform_2fcore_2fobservation_2eproto::offsets,
  file_level_metadata_energyplatform_2fcore_2fobservation_2eproto, 1, file_level_enum_descriptors_energyplatform_2fcore_2fobservation_2eproto, file_level_service_descriptors_energyplatform_2fcore_2fobservation_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_energyplatform_2fcore_2fobservation_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_energyplatform_2fcore_2fobservation_2eproto), true);
namespace energyplatform {

// ===================================================================

void Observation::InitAsDefaultInstance() {
}
class Observation::_Internal {
 public:
};

void Observation::clear_items() {
  items_.Clear();
}
Observation::Observation()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:energyplatform.Observation)
}
Observation::Observation(const Observation& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      items_(from.items_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:energyplatform.Observation)
}

void Observation::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto.base);
}

Observation::~Observation() {
  // @@protoc_insertion_point(destructor:energyplatform.Observation)
  SharedDtor();
}

void Observation::SharedDtor() {
}

void Observation::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Observation& Observation::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Observation_energyplatform_2fcore_2fobservation_2eproto.base);
  return *internal_default_instance();
}


void Observation::Clear() {
// @@protoc_insertion_point(message_clear_start:energyplatform.Observation)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  items_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Observation::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .energyplatform.PhysicalParam items = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(add_items(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 10);
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
bool Observation::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:energyplatform.Observation)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .energyplatform.PhysicalParam items = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
                input, add_items()));
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
  // @@protoc_insertion_point(parse_success:energyplatform.Observation)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:energyplatform.Observation)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Observation::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:energyplatform.Observation)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .energyplatform.PhysicalParam items = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->items_size()); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      1,
      this->items(static_cast<int>(i)),
      output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:energyplatform.Observation)
}

::PROTOBUF_NAMESPACE_ID::uint8* Observation::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:energyplatform.Observation)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .energyplatform.PhysicalParam items = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->items_size()); i < n; i++) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, this->items(static_cast<int>(i)), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:energyplatform.Observation)
  return target;
}

size_t Observation::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:energyplatform.Observation)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .energyplatform.PhysicalParam items = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->items_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          this->items(static_cast<int>(i)));
    }
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Observation::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:energyplatform.Observation)
  GOOGLE_DCHECK_NE(&from, this);
  const Observation* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Observation>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:energyplatform.Observation)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:energyplatform.Observation)
    MergeFrom(*source);
  }
}

void Observation::MergeFrom(const Observation& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:energyplatform.Observation)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  items_.MergeFrom(from.items_);
}

void Observation::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:energyplatform.Observation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Observation::CopyFrom(const Observation& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:energyplatform.Observation)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Observation::IsInitialized() const {
  return true;
}

void Observation::InternalSwap(Observation* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&items_)->InternalSwap(CastToBase(&other->items_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Observation::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::energyplatform::Observation* Arena::CreateMaybeMessage< ::energyplatform::Observation >(Arena* arena) {
  return Arena::CreateInternal< ::energyplatform::Observation >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
