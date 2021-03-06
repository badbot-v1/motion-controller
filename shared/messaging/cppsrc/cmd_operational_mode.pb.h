// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cmd_operational_mode.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_cmd_5foperational_5fmode_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_cmd_5foperational_5fmode_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include "consts.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_cmd_5foperational_5fmode_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_cmd_5foperational_5fmode_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cmd_5foperational_5fmode_2eproto;
namespace badbot {
namespace messages {
class CommandOperationalMode;
class CommandOperationalModeDefaultTypeInternal;
extern CommandOperationalModeDefaultTypeInternal _CommandOperationalMode_default_instance_;
}  // namespace messages
}  // namespace badbot
PROTOBUF_NAMESPACE_OPEN
template<> ::badbot::messages::CommandOperationalMode* Arena::CreateMaybeMessage<::badbot::messages::CommandOperationalMode>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace badbot {
namespace messages {

// ===================================================================

class CommandOperationalMode :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:badbot.messages.CommandOperationalMode) */ {
 public:
  CommandOperationalMode();
  virtual ~CommandOperationalMode();

  CommandOperationalMode(const CommandOperationalMode& from);
  CommandOperationalMode(CommandOperationalMode&& from) noexcept
    : CommandOperationalMode() {
    *this = ::std::move(from);
  }

  inline CommandOperationalMode& operator=(const CommandOperationalMode& from) {
    CopyFrom(from);
    return *this;
  }
  inline CommandOperationalMode& operator=(CommandOperationalMode&& from) noexcept {
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
  static const CommandOperationalMode& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CommandOperationalMode* internal_default_instance() {
    return reinterpret_cast<const CommandOperationalMode*>(
               &_CommandOperationalMode_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CommandOperationalMode& a, CommandOperationalMode& b) {
    a.Swap(&b);
  }
  inline void Swap(CommandOperationalMode* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline CommandOperationalMode* New() const final {
    return CreateMaybeMessage<CommandOperationalMode>(nullptr);
  }

  CommandOperationalMode* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CommandOperationalMode>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CommandOperationalMode& from);
  void MergeFrom(const CommandOperationalMode& from);
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
  void InternalSwap(CommandOperationalMode* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "badbot.messages.CommandOperationalMode";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_cmd_5foperational_5fmode_2eproto);
    return ::descriptor_table_cmd_5foperational_5fmode_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kOpModeFieldNumber = 1,
  };
  // .badbot.messages.OperationalMode opMode = 1;
  void clear_opmode();
  ::badbot::messages::OperationalMode opmode() const;
  void set_opmode(::badbot::messages::OperationalMode value);

  // @@protoc_insertion_point(class_scope:badbot.messages.CommandOperationalMode)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  int opmode_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_cmd_5foperational_5fmode_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CommandOperationalMode

// .badbot.messages.OperationalMode opMode = 1;
inline void CommandOperationalMode::clear_opmode() {
  opmode_ = 0;
}
inline ::badbot::messages::OperationalMode CommandOperationalMode::opmode() const {
  // @@protoc_insertion_point(field_get:badbot.messages.CommandOperationalMode.opMode)
  return static_cast< ::badbot::messages::OperationalMode >(opmode_);
}
inline void CommandOperationalMode::set_opmode(::badbot::messages::OperationalMode value) {
  
  opmode_ = value;
  // @@protoc_insertion_point(field_set:badbot.messages.CommandOperationalMode.opMode)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace messages
}  // namespace badbot

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_cmd_5foperational_5fmode_2eproto
