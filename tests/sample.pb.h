// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sample.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_sample_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_sample_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009002 < PROTOBUF_MIN_PROTOC_VERSION
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
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_sample_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_sample_2eproto {
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
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sample_2eproto;
namespace com {
namespace mycorp {
namespace mynamespace {
class SampleRecord;
class SampleRecordDefaultTypeInternal;
extern SampleRecordDefaultTypeInternal _SampleRecord_default_instance_;
}  // namespace mynamespace
}  // namespace mycorp
}  // namespace com
PROTOBUF_NAMESPACE_OPEN
template<> ::com::mycorp::mynamespace::SampleRecord* Arena::CreateMaybeMessage<::com::mycorp::mynamespace::SampleRecord>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace com {
namespace mycorp {
namespace mynamespace {

// ===================================================================

class SampleRecord :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:com.mycorp.mynamespace.SampleRecord) */ {
 public:
  SampleRecord();
  virtual ~SampleRecord();

  SampleRecord(const SampleRecord& from);
  SampleRecord(SampleRecord&& from) noexcept
    : SampleRecord() {
    *this = ::std::move(from);
  }

  inline SampleRecord& operator=(const SampleRecord& from) {
    CopyFrom(from);
    return *this;
  }
  inline SampleRecord& operator=(SampleRecord&& from) noexcept {
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
  static const SampleRecord& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SampleRecord* internal_default_instance() {
    return reinterpret_cast<const SampleRecord*>(
               &_SampleRecord_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(SampleRecord& a, SampleRecord& b) {
    a.Swap(&b);
  }
  inline void Swap(SampleRecord* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline SampleRecord* New() const final {
    return CreateMaybeMessage<SampleRecord>(nullptr);
  }

  SampleRecord* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<SampleRecord>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const SampleRecord& from);
  void MergeFrom(const SampleRecord& from);
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
  void InternalSwap(SampleRecord* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "com.mycorp.mynamespace.SampleRecord";
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
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_sample_2eproto);
    return ::descriptor_table_sample_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMyField2FieldNumber = 2,
    kMyField1FieldNumber = 1,
  };
  // double my_field2 = 2;
  void clear_my_field2();
  double my_field2() const;
  void set_my_field2(double value);

  // int32 my_field1 = 1;
  void clear_my_field1();
  ::PROTOBUF_NAMESPACE_ID::int32 my_field1() const;
  void set_my_field1(::PROTOBUF_NAMESPACE_ID::int32 value);

  // @@protoc_insertion_point(class_scope:com.mycorp.mynamespace.SampleRecord)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  double my_field2_;
  ::PROTOBUF_NAMESPACE_ID::int32 my_field1_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sample_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SampleRecord

// int32 my_field1 = 1;
inline void SampleRecord::clear_my_field1() {
  my_field1_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 SampleRecord::my_field1() const {
  // @@protoc_insertion_point(field_get:com.mycorp.mynamespace.SampleRecord.my_field1)
  return my_field1_;
}
inline void SampleRecord::set_my_field1(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  my_field1_ = value;
  // @@protoc_insertion_point(field_set:com.mycorp.mynamespace.SampleRecord.my_field1)
}

// double my_field2 = 2;
inline void SampleRecord::clear_my_field2() {
  my_field2_ = 0;
}
inline double SampleRecord::my_field2() const {
  // @@protoc_insertion_point(field_get:com.mycorp.mynamespace.SampleRecord.my_field2)
  return my_field2_;
}
inline void SampleRecord::set_my_field2(double value) {
  
  my_field2_ = value;
  // @@protoc_insertion_point(field_set:com.mycorp.mynamespace.SampleRecord.my_field2)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace mynamespace
}  // namespace mycorp
}  // namespace com

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_sample_2eproto