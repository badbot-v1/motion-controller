// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: imudata.proto

#include "imudata.pb.h"

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
extern PROTOBUF_INTERNAL_EXPORT_imudata_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Tuple_imudata_2eproto;
namespace badbot {
namespace messages {
class TupleDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<Tuple> _instance;
} _Tuple_default_instance_;
class ImuDataDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<ImuData> _instance;
} _ImuData_default_instance_;
}  // namespace messages
}  // namespace badbot
static void InitDefaultsscc_info_ImuData_imudata_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::badbot::messages::_ImuData_default_instance_;
    new (ptr) ::badbot::messages::ImuData();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::badbot::messages::ImuData::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_ImuData_imudata_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsscc_info_ImuData_imudata_2eproto}, {
      &scc_info_Tuple_imudata_2eproto.base,}};

static void InitDefaultsscc_info_Tuple_imudata_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::badbot::messages::_Tuple_default_instance_;
    new (ptr) ::badbot::messages::Tuple();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::badbot::messages::Tuple::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Tuple_imudata_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_Tuple_imudata_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_imudata_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_imudata_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_imudata_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_imudata_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::Tuple, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::Tuple, x_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::Tuple, y_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::Tuple, z_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, acceleration_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, orientation_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, temperature_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, pressure_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::ImuData, altitude_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::badbot::messages::Tuple)},
  { 8, -1, sizeof(::badbot::messages::ImuData)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::badbot::messages::_Tuple_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::badbot::messages::_ImuData_default_instance_),
};

const char descriptor_table_protodef_imudata_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rimudata.proto\022\017badbot.messages\"(\n\005Tupl"
  "e\022\t\n\001x\030\001 \001(\002\022\t\n\001y\030\002 \001(\002\022\t\n\001z\030\003 \001(\002\"\235\001\n\007I"
  "muData\022,\n\014acceleration\030\001 \001(\0132\026.badbot.me"
  "ssages.Tuple\022+\n\013orientation\030\002 \001(\0132\026.badb"
  "ot.messages.Tuple\022\023\n\013temperature\030\003 \001(\002\022\020"
  "\n\010pressure\030\004 \001(\002\022\020\n\010altitude\030\005 \001(\002b\006prot"
  "o3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_imudata_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_imudata_2eproto_sccs[2] = {
  &scc_info_ImuData_imudata_2eproto.base,
  &scc_info_Tuple_imudata_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_imudata_2eproto_once;
static bool descriptor_table_imudata_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_imudata_2eproto = {
  &descriptor_table_imudata_2eproto_initialized, descriptor_table_protodef_imudata_2eproto, "imudata.proto", 242,
  &descriptor_table_imudata_2eproto_once, descriptor_table_imudata_2eproto_sccs, descriptor_table_imudata_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_imudata_2eproto::offsets,
  file_level_metadata_imudata_2eproto, 2, file_level_enum_descriptors_imudata_2eproto, file_level_service_descriptors_imudata_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_imudata_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_imudata_2eproto), true);
namespace badbot {
namespace messages {

// ===================================================================

void Tuple::InitAsDefaultInstance() {
}
class Tuple::_Internal {
 public:
};

Tuple::Tuple()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:badbot.messages.Tuple)
}
Tuple::Tuple(const Tuple& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&x_, &from.x_,
    static_cast<size_t>(reinterpret_cast<char*>(&z_) -
    reinterpret_cast<char*>(&x_)) + sizeof(z_));
  // @@protoc_insertion_point(copy_constructor:badbot.messages.Tuple)
}

void Tuple::SharedCtor() {
  ::memset(&x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&z_) -
      reinterpret_cast<char*>(&x_)) + sizeof(z_));
}

Tuple::~Tuple() {
  // @@protoc_insertion_point(destructor:badbot.messages.Tuple)
  SharedDtor();
}

void Tuple::SharedDtor() {
}

void Tuple::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Tuple& Tuple::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_Tuple_imudata_2eproto.base);
  return *internal_default_instance();
}


void Tuple::Clear() {
// @@protoc_insertion_point(message_clear_start:badbot.messages.Tuple)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&z_) -
      reinterpret_cast<char*>(&x_)) + sizeof(z_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Tuple::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // float x = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 13)) {
          x_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float y = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 21)) {
          y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float z = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          z_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
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
bool Tuple::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:badbot.messages.Tuple)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // float x = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (13 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &x_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float y = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (21 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &y_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float z = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (29 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &z_)));
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
  // @@protoc_insertion_point(parse_success:badbot.messages.Tuple)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:badbot.messages.Tuple)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Tuple::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:badbot.messages.Tuple)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // float x = 1;
  if (!(this->x() <= 0 && this->x() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(1, this->x(), output);
  }

  // float y = 2;
  if (!(this->y() <= 0 && this->y() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(2, this->y(), output);
  }

  // float z = 3;
  if (!(this->z() <= 0 && this->z() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(3, this->z(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:badbot.messages.Tuple)
}

::PROTOBUF_NAMESPACE_ID::uint8* Tuple::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:badbot.messages.Tuple)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // float x = 1;
  if (!(this->x() <= 0 && this->x() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(1, this->x(), target);
  }

  // float y = 2;
  if (!(this->y() <= 0 && this->y() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(2, this->y(), target);
  }

  // float z = 3;
  if (!(this->z() <= 0 && this->z() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->z(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:badbot.messages.Tuple)
  return target;
}

size_t Tuple::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:badbot.messages.Tuple)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // float x = 1;
  if (!(this->x() <= 0 && this->x() >= 0)) {
    total_size += 1 + 4;
  }

  // float y = 2;
  if (!(this->y() <= 0 && this->y() >= 0)) {
    total_size += 1 + 4;
  }

  // float z = 3;
  if (!(this->z() <= 0 && this->z() >= 0)) {
    total_size += 1 + 4;
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Tuple::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:badbot.messages.Tuple)
  GOOGLE_DCHECK_NE(&from, this);
  const Tuple* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<Tuple>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:badbot.messages.Tuple)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:badbot.messages.Tuple)
    MergeFrom(*source);
  }
}

void Tuple::MergeFrom(const Tuple& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:badbot.messages.Tuple)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!(from.x() <= 0 && from.x() >= 0)) {
    set_x(from.x());
  }
  if (!(from.y() <= 0 && from.y() >= 0)) {
    set_y(from.y());
  }
  if (!(from.z() <= 0 && from.z() >= 0)) {
    set_z(from.z());
  }
}

void Tuple::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:badbot.messages.Tuple)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Tuple::CopyFrom(const Tuple& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:badbot.messages.Tuple)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Tuple::IsInitialized() const {
  return true;
}

void Tuple::InternalSwap(Tuple* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(x_, other->x_);
  swap(y_, other->y_);
  swap(z_, other->z_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Tuple::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void ImuData::InitAsDefaultInstance() {
  ::badbot::messages::_ImuData_default_instance_._instance.get_mutable()->acceleration_ = const_cast< ::badbot::messages::Tuple*>(
      ::badbot::messages::Tuple::internal_default_instance());
  ::badbot::messages::_ImuData_default_instance_._instance.get_mutable()->orientation_ = const_cast< ::badbot::messages::Tuple*>(
      ::badbot::messages::Tuple::internal_default_instance());
}
class ImuData::_Internal {
 public:
  static const ::badbot::messages::Tuple& acceleration(const ImuData* msg);
  static const ::badbot::messages::Tuple& orientation(const ImuData* msg);
};

const ::badbot::messages::Tuple&
ImuData::_Internal::acceleration(const ImuData* msg) {
  return *msg->acceleration_;
}
const ::badbot::messages::Tuple&
ImuData::_Internal::orientation(const ImuData* msg) {
  return *msg->orientation_;
}
ImuData::ImuData()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:badbot.messages.ImuData)
}
ImuData::ImuData(const ImuData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_acceleration()) {
    acceleration_ = new ::badbot::messages::Tuple(*from.acceleration_);
  } else {
    acceleration_ = nullptr;
  }
  if (from.has_orientation()) {
    orientation_ = new ::badbot::messages::Tuple(*from.orientation_);
  } else {
    orientation_ = nullptr;
  }
  ::memcpy(&temperature_, &from.temperature_,
    static_cast<size_t>(reinterpret_cast<char*>(&altitude_) -
    reinterpret_cast<char*>(&temperature_)) + sizeof(altitude_));
  // @@protoc_insertion_point(copy_constructor:badbot.messages.ImuData)
}

void ImuData::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_ImuData_imudata_2eproto.base);
  ::memset(&acceleration_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&altitude_) -
      reinterpret_cast<char*>(&acceleration_)) + sizeof(altitude_));
}

ImuData::~ImuData() {
  // @@protoc_insertion_point(destructor:badbot.messages.ImuData)
  SharedDtor();
}

void ImuData::SharedDtor() {
  if (this != internal_default_instance()) delete acceleration_;
  if (this != internal_default_instance()) delete orientation_;
}

void ImuData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ImuData& ImuData::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_ImuData_imudata_2eproto.base);
  return *internal_default_instance();
}


void ImuData::Clear() {
// @@protoc_insertion_point(message_clear_start:badbot.messages.ImuData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (GetArenaNoVirtual() == nullptr && acceleration_ != nullptr) {
    delete acceleration_;
  }
  acceleration_ = nullptr;
  if (GetArenaNoVirtual() == nullptr && orientation_ != nullptr) {
    delete orientation_;
  }
  orientation_ = nullptr;
  ::memset(&temperature_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&altitude_) -
      reinterpret_cast<char*>(&temperature_)) + sizeof(altitude_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* ImuData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .badbot.messages.Tuple acceleration = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(mutable_acceleration(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .badbot.messages.Tuple orientation = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(mutable_orientation(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // float temperature = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          temperature_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float pressure = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 37)) {
          pressure_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      // float altitude = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 45)) {
          altitude_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
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
bool ImuData::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:badbot.messages.ImuData)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // .badbot.messages.Tuple acceleration = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (10 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
               input, mutable_acceleration()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // .badbot.messages.Tuple orientation = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (18 & 0xFF)) {
          DO_(::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadMessage(
               input, mutable_orientation()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float temperature = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (29 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &temperature_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float pressure = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (37 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &pressure_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // float altitude = 5;
      case 5: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (45 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   float, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &altitude_)));
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
  // @@protoc_insertion_point(parse_success:badbot.messages.ImuData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:badbot.messages.ImuData)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void ImuData::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:badbot.messages.ImuData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .badbot.messages.Tuple acceleration = 1;
  if (this->has_acceleration()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, _Internal::acceleration(this), output);
  }

  // .badbot.messages.Tuple orientation = 2;
  if (this->has_orientation()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, _Internal::orientation(this), output);
  }

  // float temperature = 3;
  if (!(this->temperature() <= 0 && this->temperature() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(3, this->temperature(), output);
  }

  // float pressure = 4;
  if (!(this->pressure() <= 0 && this->pressure() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(4, this->pressure(), output);
  }

  // float altitude = 5;
  if (!(this->altitude() <= 0 && this->altitude() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloat(5, this->altitude(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:badbot.messages.ImuData)
}

::PROTOBUF_NAMESPACE_ID::uint8* ImuData::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:badbot.messages.ImuData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .badbot.messages.Tuple acceleration = 1;
  if (this->has_acceleration()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        1, _Internal::acceleration(this), target);
  }

  // .badbot.messages.Tuple orientation = 2;
  if (this->has_orientation()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessageToArray(
        2, _Internal::orientation(this), target);
  }

  // float temperature = 3;
  if (!(this->temperature() <= 0 && this->temperature() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->temperature(), target);
  }

  // float pressure = 4;
  if (!(this->pressure() <= 0 && this->pressure() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(4, this->pressure(), target);
  }

  // float altitude = 5;
  if (!(this->altitude() <= 0 && this->altitude() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(5, this->altitude(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:badbot.messages.ImuData)
  return target;
}

size_t ImuData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:badbot.messages.ImuData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // .badbot.messages.Tuple acceleration = 1;
  if (this->has_acceleration()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *acceleration_);
  }

  // .badbot.messages.Tuple orientation = 2;
  if (this->has_orientation()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *orientation_);
  }

  // float temperature = 3;
  if (!(this->temperature() <= 0 && this->temperature() >= 0)) {
    total_size += 1 + 4;
  }

  // float pressure = 4;
  if (!(this->pressure() <= 0 && this->pressure() >= 0)) {
    total_size += 1 + 4;
  }

  // float altitude = 5;
  if (!(this->altitude() <= 0 && this->altitude() >= 0)) {
    total_size += 1 + 4;
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ImuData::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:badbot.messages.ImuData)
  GOOGLE_DCHECK_NE(&from, this);
  const ImuData* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ImuData>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:badbot.messages.ImuData)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:badbot.messages.ImuData)
    MergeFrom(*source);
  }
}

void ImuData::MergeFrom(const ImuData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:badbot.messages.ImuData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.has_acceleration()) {
    mutable_acceleration()->::badbot::messages::Tuple::MergeFrom(from.acceleration());
  }
  if (from.has_orientation()) {
    mutable_orientation()->::badbot::messages::Tuple::MergeFrom(from.orientation());
  }
  if (!(from.temperature() <= 0 && from.temperature() >= 0)) {
    set_temperature(from.temperature());
  }
  if (!(from.pressure() <= 0 && from.pressure() >= 0)) {
    set_pressure(from.pressure());
  }
  if (!(from.altitude() <= 0 && from.altitude() >= 0)) {
    set_altitude(from.altitude());
  }
}

void ImuData::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:badbot.messages.ImuData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ImuData::CopyFrom(const ImuData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:badbot.messages.ImuData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ImuData::IsInitialized() const {
  return true;
}

void ImuData::InternalSwap(ImuData* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(acceleration_, other->acceleration_);
  swap(orientation_, other->orientation_);
  swap(temperature_, other->temperature_);
  swap(pressure_, other->pressure_);
  swap(altitude_, other->altitude_);
}

::PROTOBUF_NAMESPACE_ID::Metadata ImuData::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace messages
}  // namespace badbot
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::badbot::messages::Tuple* Arena::CreateMaybeMessage< ::badbot::messages::Tuple >(Arena* arena) {
  return Arena::CreateInternal< ::badbot::messages::Tuple >(arena);
}
template<> PROTOBUF_NOINLINE ::badbot::messages::ImuData* Arena::CreateMaybeMessage< ::badbot::messages::ImuData >(Arena* arena) {
  return Arena::CreateInternal< ::badbot::messages::ImuData >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
