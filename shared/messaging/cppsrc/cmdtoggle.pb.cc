// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cmdtoggle.proto

#include "cmdtoggle.pb.h"

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
namespace badbot {
namespace messages {
class CommandToggleDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<CommandToggle> _instance;
} _CommandToggle_default_instance_;
}  // namespace messages
}  // namespace badbot
static void InitDefaultsscc_info_CommandToggle_cmdtoggle_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::badbot::messages::_CommandToggle_default_instance_;
    new (ptr) ::badbot::messages::CommandToggle();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::badbot::messages::CommandToggle::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_CommandToggle_cmdtoggle_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_CommandToggle_cmdtoggle_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_cmdtoggle_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_cmdtoggle_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_cmdtoggle_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_cmdtoggle_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::CommandToggle, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::CommandToggle, device_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::CommandToggle, enable_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::badbot::messages::CommandToggle)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::badbot::messages::_CommandToggle_default_instance_),
};

const char descriptor_table_protodef_cmdtoggle_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\017cmdtoggle.proto\022\017badbot.messages\032\014cons"
  "ts.proto\"I\n\rCommandToggle\022(\n\006device\030\001 \001("
  "\0162\030.badbot.messages.Devices\022\016\n\006enable\030\002 "
  "\001(\010b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_cmdtoggle_2eproto_deps[1] = {
  &::descriptor_table_consts_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_cmdtoggle_2eproto_sccs[1] = {
  &scc_info_CommandToggle_cmdtoggle_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_cmdtoggle_2eproto_once;
static bool descriptor_table_cmdtoggle_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cmdtoggle_2eproto = {
  &descriptor_table_cmdtoggle_2eproto_initialized, descriptor_table_protodef_cmdtoggle_2eproto, "cmdtoggle.proto", 131,
  &descriptor_table_cmdtoggle_2eproto_once, descriptor_table_cmdtoggle_2eproto_sccs, descriptor_table_cmdtoggle_2eproto_deps, 1, 1,
  schemas, file_default_instances, TableStruct_cmdtoggle_2eproto::offsets,
  file_level_metadata_cmdtoggle_2eproto, 1, file_level_enum_descriptors_cmdtoggle_2eproto, file_level_service_descriptors_cmdtoggle_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_cmdtoggle_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_cmdtoggle_2eproto), true);
namespace badbot {
namespace messages {

// ===================================================================

void CommandToggle::InitAsDefaultInstance() {
}
class CommandToggle::_Internal {
 public:
};

CommandToggle::CommandToggle()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:badbot.messages.CommandToggle)
}
CommandToggle::CommandToggle(const CommandToggle& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&device_, &from.device_,
    static_cast<size_t>(reinterpret_cast<char*>(&enable_) -
    reinterpret_cast<char*>(&device_)) + sizeof(enable_));
  // @@protoc_insertion_point(copy_constructor:badbot.messages.CommandToggle)
}

void CommandToggle::SharedCtor() {
  ::memset(&device_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&enable_) -
      reinterpret_cast<char*>(&device_)) + sizeof(enable_));
}

CommandToggle::~CommandToggle() {
  // @@protoc_insertion_point(destructor:badbot.messages.CommandToggle)
  SharedDtor();
}

void CommandToggle::SharedDtor() {
}

void CommandToggle::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const CommandToggle& CommandToggle::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_CommandToggle_cmdtoggle_2eproto.base);
  return *internal_default_instance();
}


void CommandToggle::Clear() {
// @@protoc_insertion_point(message_clear_start:badbot.messages.CommandToggle)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&device_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&enable_) -
      reinterpret_cast<char*>(&device_)) + sizeof(enable_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* CommandToggle::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .badbot.messages.Devices device = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
          set_device(static_cast<::badbot::messages::Devices>(val));
        } else goto handle_unusual;
        continue;
      // bool enable = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          enable_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool CommandToggle::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:badbot.messages.CommandToggle)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .badbot.messages.Devices device = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (8 & 0xFF)) {
          int value = 0;
          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   int, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          set_device(static_cast< ::badbot::messages::Devices >(value));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // bool enable = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (16 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   bool, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_BOOL>(
                 input, &enable_)));
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
  // @@protoc_insertion_point(parse_success:badbot.messages.CommandToggle)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:badbot.messages.CommandToggle)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void CommandToggle::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:badbot.messages.CommandToggle)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .badbot.messages.Devices device = 1;
  if (this->device() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnum(
      1, this->device(), output);
  }

  // bool enable = 2;
  if (this->enable() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBool(2, this->enable(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:badbot.messages.CommandToggle)
}

::PROTOBUF_NAMESPACE_ID::uint8* CommandToggle::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:badbot.messages.CommandToggle)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .badbot.messages.Devices device = 1;
  if (this->device() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->device(), target);
  }

  // bool enable = 2;
  if (this->enable() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(2, this->enable(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:badbot.messages.CommandToggle)
  return target;
}

size_t CommandToggle::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:badbot.messages.CommandToggle)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .badbot.messages.Devices device = 1;
  if (this->device() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->device());
  }

  // bool enable = 2;
  if (this->enable() != 0) {
    total_size += 1 + 1;
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void CommandToggle::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:badbot.messages.CommandToggle)
  GOOGLE_DCHECK_NE(&from, this);
  const CommandToggle* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<CommandToggle>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:badbot.messages.CommandToggle)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:badbot.messages.CommandToggle)
    MergeFrom(*source);
  }
}

void CommandToggle::MergeFrom(const CommandToggle& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:badbot.messages.CommandToggle)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.device() != 0) {
    set_device(from.device());
  }
  if (from.enable() != 0) {
    set_enable(from.enable());
  }
}

void CommandToggle::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:badbot.messages.CommandToggle)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CommandToggle::CopyFrom(const CommandToggle& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:badbot.messages.CommandToggle)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CommandToggle::IsInitialized() const {
  return true;
}

void CommandToggle::InternalSwap(CommandToggle* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(device_, other->device_);
  swap(enable_, other->enable_);
}

::PROTOBUF_NAMESPACE_ID::Metadata CommandToggle::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace messages
}  // namespace badbot
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::badbot::messages::CommandToggle* Arena::CreateMaybeMessage< ::badbot::messages::CommandToggle >(Arena* arena) {
  return Arena::CreateInternal< ::badbot::messages::CommandToggle >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
