#include "pch.h"
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: energyplatform/core/action.proto

#include "energyplatform/core/action.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_energyplatform_2fcore_2foptimization_5fparam_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_OptimizationParameter_energyplatform_2fcore_2foptimization_5fparam_2eproto;
namespace energyplatform {
class ActionDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Action> _instance;
} _Action_default_instance_;
}  // namespace energyplatform
static void InitDefaultsscc_info_Action_energyplatform_2fcore_2faction_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::energyplatform::_Action_default_instance_;
    new (ptr) ::energyplatform::Action();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::energyplatform::Action::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_Action_energyplatform_2fcore_2faction_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_Action_energyplatform_2fcore_2faction_2eproto}, {
      &scc_info_OptimizationParameter_energyplatform_2fcore_2foptimization_5fparam_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_energyplatform_2fcore_2faction_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_energyplatform_2fcore_2faction_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_energyplatform_2fcore_2faction_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_energyplatform_2fcore_2faction_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::energyplatform::Action, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::energyplatform::Action, optimization_params_),
  PROTOBUF_FIELD_OFFSET(::energyplatform::Action, info_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::energyplatform::Action)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::energyplatform::_Action_default_instance_),
};

const char descriptor_table_protodef_energyplatform_2fcore_2faction_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n energyplatform/core/action.proto\022\016ener"
  "gyplatform\032,energyplatform/core/optimiza"
  "tion_param.proto\"Z\n\006Action\022B\n\023optimizati"
  "on_params\030\001 \003(\0132%.energyplatform.Optimiz"
  "ationParameter\022\014\n\004info\030\002 \001(\tb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_energyplatform_2fcore_2faction_2eproto_deps[1] = {
  &::descriptor_table_energyplatform_2fcore_2foptimization_5fparam_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_energyplatform_2fcore_2faction_2eproto_sccs[1] = {
  &scc_info_Action_energyplatform_2fcore_2faction_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_energyplatform_2fcore_2faction_2eproto_once;
static bool descriptor_table_energyplatform_2fcore_2faction_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_energyplatform_2fcore_2faction_2eproto = {
  &descriptor_table_energyplatform_2fcore_2faction_2eproto_initialized, descriptor_table_protodef_energyplatform_2fcore_2faction_2eproto, "energyplatform/core/action.proto", 196,
  &descriptor_table_energyplatform_2fcore_2faction_2eproto_once, descriptor_table_energyplatform_2fcore_2faction_2eproto_sccs, descriptor_table_energyplatform_2fcore_2faction_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_energyplatform_2fcore_2faction_2eproto::offsets,
  file_level_metadata_energyplatform_2fcore_2faction_2eproto, 1, file_level_enum_descriptors_energyplatform_2fcore_2faction_2eproto, file_level_service_descriptors_energyplatform_2fcore_2faction_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_energyplatform_2fcore_2faction_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_energyplatform_2fcore_2faction_2eproto), true);
namespace energyplatform {

// ===================================================================

void Action::InitAsDefaultInstance() {
}
class Action::_Internal {
 public:
};

void Action::clear_optimization_params() {
  optimization_params_.Clear();
}
Action::Action()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:energyplatform.Action)
}
Action::Action(const Action& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      optimization_params_(from.optimization_params_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  info_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from.info().empty()) {
    info_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.info_);
  }
  // @@protoc_insertion_point(copy_constructor:energyplatform.Action)
}

void Action::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_Action_energyplatform_2fcore_2faction_2eproto.base);
  info_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

Action::~Action() {
  // @@protoc_insertion_point(destructor:energyplatform.Action)
  SharedDtor();
}

void Action::SharedDtor() {
  info_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void Action::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Action& Action::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Action_energyplatform_2fcore_2faction_2eproto.base);
  return *internal_default_instance();
}


void Action::Clear() {
// @@protoc_insertion_point(message_clear_start:energyplatform.Action)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  optimization_params_.Clear();
  info_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Action::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // repeated .energyplatform.OptimizationParameter optimization_params = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(add_optimization_params(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint8>(ptr) == 10);
        } else goto handle_unusual;
        continue;
      // string info = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParserUTF8(mutable_info(), ptr, ctx, "energyplatform.Action.info");
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
bool Action::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:energyplatform.Action)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .energyplatform.OptimizationParameter optimization_params = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
                input, add_optimization_params()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // string info = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadString(
                input, this->mutable_info()));
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
            this->info().data(), static_cast<int>(this->info().length()),
            ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::PARSE,
            "energyplatform.Action.info"));
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
  // @@protoc_insertion_point(parse_success:energyplatform.Action)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:energyplatform.Action)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Action::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:energyplatform.Action)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .energyplatform.OptimizationParameter optimization_params = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->optimization_params_size()); i < n; i++) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      1,
      this->optimization_params(static_cast<int>(i)),
      output);
  }

  // string info = 2;
  if (this->info().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->info().data(), static_cast<int>(this->info().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "energyplatform.Action.info");
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->info(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:energyplatform.Action)
}

::PROTOBUF_NAMESPACE_ID::uint8* Action::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:energyplatform.Action)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .energyplatform.OptimizationParameter optimization_params = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->optimization_params_size()); i < n; i++) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, this->optimization_params(static_cast<int>(i)), target);
  }

  // string info = 2;
  if (this->info().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->info().data(), static_cast<int>(this->info().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "energyplatform.Action.info");
    target =
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteStringToArray(
        2, this->info(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:energyplatform.Action)
  return target;
}

size_t Action::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:energyplatform.Action)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .energyplatform.OptimizationParameter optimization_params = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->optimization_params_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          this->optimization_params(static_cast<int>(i)));
    }
  }

  // string info = 2;
  if (this->info().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->info());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Action::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:energyplatform.Action)
  GOOGLE_DCHECK_NE(&from, this);
  const Action* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Action>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:energyplatform.Action)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:energyplatform.Action)
    MergeFrom(*source);
  }
}

void Action::MergeFrom(const Action& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:energyplatform.Action)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  optimization_params_.MergeFrom(from.optimization_params_);
  if (from.info().size() > 0) {

    info_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.info_);
  }
}

void Action::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:energyplatform.Action)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Action::CopyFrom(const Action& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:energyplatform.Action)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Action::IsInitialized() const {
  return true;
}

void Action::InternalSwap(Action* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  CastToBase(&optimization_params_)->InternalSwap(CastToBase(&other->optimization_params_));
  info_.Swap(&other->info_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::PROTOBUF_NAMESPACE_ID::Metadata Action::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace energyplatform
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::energyplatform::Action* Arena::CreateMaybeMessage< ::energyplatform::Action >(Arena* arena) {
  return Arena::CreateInternal< ::energyplatform::Action >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
