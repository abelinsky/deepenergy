#include "pch.h"
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: unetwork/core/tasks.proto

#include "unetwork/core/tasks.pb.h"

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
namespace unetwork {
}  // namespace unetwork
static constexpr ::PROTOBUF_NAMESPACE_ID::Metadata* file_level_metadata_unetwork_2fcore_2ftasks_2eproto = nullptr;
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_unetwork_2fcore_2ftasks_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_unetwork_2fcore_2ftasks_2eproto = nullptr;
const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_unetwork_2fcore_2ftasks_2eproto::offsets[1] = {};
static constexpr ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema* schemas = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_unetwork_2fcore_2ftasks_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\031unetwork/core/tasks.proto\022\010unetwork*o\n"
  "\nSystemTask\022\r\n\tUNDEFINED\020\000\022\020\n\014FEED_FORWA"
  "RD\020\001\022 \n\034AVAILABLE_TECHNOLOGICAL_MODE\020\002\022\022"
  "\n\016MAX_THROUGHPUT\020\003\022\n\n\006SIMPLE\020\004b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_unetwork_2fcore_2ftasks_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_unetwork_2fcore_2ftasks_2eproto_sccs[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_unetwork_2fcore_2ftasks_2eproto_once;
static bool descriptor_table_unetwork_2fcore_2ftasks_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_unetwork_2fcore_2ftasks_2eproto = {
  &descriptor_table_unetwork_2fcore_2ftasks_2eproto_initialized, descriptor_table_protodef_unetwork_2fcore_2ftasks_2eproto, "unetwork/core/tasks.proto", 158,
  &descriptor_table_unetwork_2fcore_2ftasks_2eproto_once, descriptor_table_unetwork_2fcore_2ftasks_2eproto_sccs, descriptor_table_unetwork_2fcore_2ftasks_2eproto_deps, 0, 0,
  schemas, file_default_instances, TableStruct_unetwork_2fcore_2ftasks_2eproto::offsets,
  file_level_metadata_unetwork_2fcore_2ftasks_2eproto, 0, file_level_enum_descriptors_unetwork_2fcore_2ftasks_2eproto, file_level_service_descriptors_unetwork_2fcore_2ftasks_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_unetwork_2fcore_2ftasks_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_unetwork_2fcore_2ftasks_2eproto), true);
namespace unetwork {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* SystemTask_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_unetwork_2fcore_2ftasks_2eproto);
  return file_level_enum_descriptors_unetwork_2fcore_2ftasks_2eproto[0];
}
bool SystemTask_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace unetwork
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
