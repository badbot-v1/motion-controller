// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: gpsdata.proto

#include "gpsdata.pb.h"

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
class GpsDataDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<GpsData> _instance;
} _GpsData_default_instance_;
}  // namespace messages
}  // namespace badbot
static void InitDefaultsscc_info_GpsData_gpsdata_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::badbot::messages::_GpsData_default_instance_;
    new (ptr) ::badbot::messages::GpsData();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::badbot::messages::GpsData::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_GpsData_gpsdata_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsscc_info_GpsData_gpsdata_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_gpsdata_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_gpsdata_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_gpsdata_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_gpsdata_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, latitude_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, longitude_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, hdop_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, vdop_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, pdop_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, satellites_visible_),
  PROTOBUF_FIELD_OFFSET(::badbot::messages::GpsData, satellites_used_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::badbot::messages::GpsData)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::badbot::messages::_GpsData_default_instance_),
};

const char descriptor_table_protodef_gpsdata_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\rgpsdata.proto\022\017badbot.messages\"\215\001\n\007Gps"
  "Data\022\020\n\010latitude\030\001 \001(\001\022\021\n\tlongitude\030\002 \001("
  "\001\022\014\n\004hdop\030\003 \001(\001\022\014\n\004vdop\030\004 \001(\001\022\014\n\004pdop\030\005 "
  "\001(\001\022\032\n\022satellites_visible\030\006 \001(\005\022\027\n\017satel"
  "lites_used\030\007 \001(\005b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_gpsdata_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_gpsdata_2eproto_sccs[1] = {
  &scc_info_GpsData_gpsdata_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_gpsdata_2eproto_once;
static bool descriptor_table_gpsdata_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_gpsdata_2eproto = {
  &descriptor_table_gpsdata_2eproto_initialized, descriptor_table_protodef_gpsdata_2eproto, "gpsdata.proto", 184,
  &descriptor_table_gpsdata_2eproto_once, descriptor_table_gpsdata_2eproto_sccs, descriptor_table_gpsdata_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_gpsdata_2eproto::offsets,
  file_level_metadata_gpsdata_2eproto, 1, file_level_enum_descriptors_gpsdata_2eproto, file_level_service_descriptors_gpsdata_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_gpsdata_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_gpsdata_2eproto), true);
namespace badbot {
namespace messages {

// ===================================================================

void GpsData::InitAsDefaultInstance() {
}
class GpsData::_Internal {
 public:
};

GpsData::GpsData()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:badbot.messages.GpsData)
}
GpsData::GpsData(const GpsData& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&latitude_, &from.latitude_,
    static_cast<size_t>(reinterpret_cast<char*>(&satellites_used_) -
    reinterpret_cast<char*>(&latitude_)) + sizeof(satellites_used_));
  // @@protoc_insertion_point(copy_constructor:badbot.messages.GpsData)
}

void GpsData::SharedCtor() {
  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&satellites_used_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(satellites_used_));
}

GpsData::~GpsData() {
  // @@protoc_insertion_point(destructor:badbot.messages.GpsData)
  SharedDtor();
}

void GpsData::SharedDtor() {
}

void GpsData::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const GpsData& GpsData::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_GpsData_gpsdata_2eproto.base);
  return *internal_default_instance();
}


void GpsData::Clear() {
// @@protoc_insertion_point(message_clear_start:badbot.messages.GpsData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&satellites_used_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(satellites_used_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* GpsData::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // double latitude = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 9)) {
          latitude_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // double longitude = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 17)) {
          longitude_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // double hdop = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 25)) {
          hdop_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // double vdop = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 33)) {
          vdop_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // double pdop = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 41)) {
          pdop_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // int32 satellites_visible = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 48)) {
          satellites_visible_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 satellites_used = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          satellites_used_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
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
bool GpsData::MergePartialFromCodedStream(
    ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::PROTOBUF_NAMESPACE_ID::uint32 tag;
  // @@protoc_insertion_point(parse_start:badbot.messages.GpsData)
  for (;;) {
    ::std::pair<::PROTOBUF_NAMESPACE_ID::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // double latitude = 1;
      case 1: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (9 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &latitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double longitude = 2;
      case 2: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (17 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &longitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double hdop = 3;
      case 3: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (25 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &hdop_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double vdop = 4;
      case 4: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (33 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &vdop_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double pdop = 5;
      case 5: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (41 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   double, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &pdop_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 satellites_visible = 6;
      case 6: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (48 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
                 input, &satellites_visible_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int32 satellites_used = 7;
      case 7: {
        if (static_cast< ::PROTOBUF_NAMESPACE_ID::uint8>(tag) == (56 & 0xFF)) {

          DO_((::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::ReadPrimitive<
                   ::PROTOBUF_NAMESPACE_ID::int32, ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::TYPE_INT32>(
                 input, &satellites_used_)));
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
  // @@protoc_insertion_point(parse_success:badbot.messages.GpsData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:badbot.messages.GpsData)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void GpsData::SerializeWithCachedSizes(
    ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:badbot.messages.GpsData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (!(this->latitude() <= 0 && this->latitude() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(1, this->latitude(), output);
  }

  // double longitude = 2;
  if (!(this->longitude() <= 0 && this->longitude() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(2, this->longitude(), output);
  }

  // double hdop = 3;
  if (!(this->hdop() <= 0 && this->hdop() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(3, this->hdop(), output);
  }

  // double vdop = 4;
  if (!(this->vdop() <= 0 && this->vdop() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(4, this->vdop(), output);
  }

  // double pdop = 5;
  if (!(this->pdop() <= 0 && this->pdop() >= 0)) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDouble(5, this->pdop(), output);
  }

  // int32 satellites_visible = 6;
  if (this->satellites_visible() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(6, this->satellites_visible(), output);
  }

  // int32 satellites_used = 7;
  if (this->satellites_used() != 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32(7, this->satellites_used(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:badbot.messages.GpsData)
}

::PROTOBUF_NAMESPACE_ID::uint8* GpsData::InternalSerializeWithCachedSizesToArray(
    ::PROTOBUF_NAMESPACE_ID::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:badbot.messages.GpsData)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (!(this->latitude() <= 0 && this->latitude() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(1, this->latitude(), target);
  }

  // double longitude = 2;
  if (!(this->longitude() <= 0 && this->longitude() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(2, this->longitude(), target);
  }

  // double hdop = 3;
  if (!(this->hdop() <= 0 && this->hdop() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(3, this->hdop(), target);
  }

  // double vdop = 4;
  if (!(this->vdop() <= 0 && this->vdop() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(4, this->vdop(), target);
  }

  // double pdop = 5;
  if (!(this->pdop() <= 0 && this->pdop() >= 0)) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(5, this->pdop(), target);
  }

  // int32 satellites_visible = 6;
  if (this->satellites_visible() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(6, this->satellites_visible(), target);
  }

  // int32 satellites_used = 7;
  if (this->satellites_used() != 0) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(7, this->satellites_used(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:badbot.messages.GpsData)
  return target;
}

size_t GpsData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:badbot.messages.GpsData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double latitude = 1;
  if (!(this->latitude() <= 0 && this->latitude() >= 0)) {
    total_size += 1 + 8;
  }

  // double longitude = 2;
  if (!(this->longitude() <= 0 && this->longitude() >= 0)) {
    total_size += 1 + 8;
  }

  // double hdop = 3;
  if (!(this->hdop() <= 0 && this->hdop() >= 0)) {
    total_size += 1 + 8;
  }

  // double vdop = 4;
  if (!(this->vdop() <= 0 && this->vdop() >= 0)) {
    total_size += 1 + 8;
  }

  // double pdop = 5;
  if (!(this->pdop() <= 0 && this->pdop() >= 0)) {
    total_size += 1 + 8;
  }

  // int32 satellites_visible = 6;
  if (this->satellites_visible() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->satellites_visible());
  }

  // int32 satellites_used = 7;
  if (this->satellites_used() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->satellites_used());
  }

  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GpsData::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:badbot.messages.GpsData)
  GOOGLE_DCHECK_NE(&from, this);
  const GpsData* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GpsData>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:badbot.messages.GpsData)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:badbot.messages.GpsData)
    MergeFrom(*source);
  }
}

void GpsData::MergeFrom(const GpsData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:badbot.messages.GpsData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (!(from.latitude() <= 0 && from.latitude() >= 0)) {
    set_latitude(from.latitude());
  }
  if (!(from.longitude() <= 0 && from.longitude() >= 0)) {
    set_longitude(from.longitude());
  }
  if (!(from.hdop() <= 0 && from.hdop() >= 0)) {
    set_hdop(from.hdop());
  }
  if (!(from.vdop() <= 0 && from.vdop() >= 0)) {
    set_vdop(from.vdop());
  }
  if (!(from.pdop() <= 0 && from.pdop() >= 0)) {
    set_pdop(from.pdop());
  }
  if (from.satellites_visible() != 0) {
    set_satellites_visible(from.satellites_visible());
  }
  if (from.satellites_used() != 0) {
    set_satellites_used(from.satellites_used());
  }
}

void GpsData::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:badbot.messages.GpsData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GpsData::CopyFrom(const GpsData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:badbot.messages.GpsData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GpsData::IsInitialized() const {
  return true;
}

void GpsData::InternalSwap(GpsData* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(latitude_, other->latitude_);
  swap(longitude_, other->longitude_);
  swap(hdop_, other->hdop_);
  swap(vdop_, other->vdop_);
  swap(pdop_, other->pdop_);
  swap(satellites_visible_, other->satellites_visible_);
  swap(satellites_used_, other->satellites_used_);
}

::PROTOBUF_NAMESPACE_ID::Metadata GpsData::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace messages
}  // namespace badbot
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::badbot::messages::GpsData* Arena::CreateMaybeMessage< ::badbot::messages::GpsData >(Arena* arena) {
  return Arena::CreateInternal< ::badbot::messages::GpsData >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
