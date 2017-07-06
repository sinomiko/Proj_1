// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: addressbook.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "addressbook.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace tutorial {
class PersionDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<Persion> {
} _Persion_default_instance_;
class AddressBookDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<AddressBook> {
} _AddressBook_default_instance_;

namespace protobuf_addressbook_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[2];

}  // namespace

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTableField
    const TableStruct::entries[] = {
  {0, 0, 0, ::google::protobuf::internal::kInvalidMask, 0, 0},
};

PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::AuxillaryParseTableField
    const TableStruct::aux[] = {
  ::google::protobuf::internal::AuxillaryParseTableField(),
};
PROTOBUF_CONSTEXPR_VAR ::google::protobuf::internal::ParseTable const
    TableStruct::schema[] = {
  { NULL, NULL, 0, -1, -1, false },
  { NULL, NULL, 0, -1, -1, false },
};

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Persion, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Persion, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Persion, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Persion, age_),
  0,
  1,
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressBook, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressBook, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AddressBook, persion_),
  ~0u,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(Persion)},
  { 9, 15, sizeof(AddressBook)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_Persion_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&_AddressBook_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "addressbook.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 2);
}

}  // namespace

void TableStruct::Shutdown() {
  _Persion_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
  _AddressBook_default_instance_.Shutdown();
  delete file_level_metadata[1].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _Persion_default_instance_.DefaultConstruct();
  _AddressBook_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\021addressbook.proto\022\010tutorial\"$\n\007Persion"
      "\022\014\n\004name\030\001 \002(\t\022\013\n\003age\030\002 \002(\005\"1\n\013AddressBo"
      "ok\022\"\n\007persion\030\001 \003(\0132\021.tutorial.Persion"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 118);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "addressbook.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_addressbook_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Persion::kNameFieldNumber;
const int Persion::kAgeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Persion::Persion()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_addressbook_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:tutorial.Persion)
}
Persion::Persion(const Persion& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  age_ = from.age_;
  // @@protoc_insertion_point(copy_constructor:tutorial.Persion)
}

void Persion::SharedCtor() {
  _cached_size_ = 0;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  age_ = 0;
}

Persion::~Persion() {
  // @@protoc_insertion_point(destructor:tutorial.Persion)
  SharedDtor();
}

void Persion::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Persion::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Persion::descriptor() {
  protobuf_addressbook_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_addressbook_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const Persion& Persion::default_instance() {
  protobuf_addressbook_2eproto::InitDefaults();
  return *internal_default_instance();
}

Persion* Persion::New(::google::protobuf::Arena* arena) const {
  Persion* n = new Persion;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void Persion::Clear() {
// @@protoc_insertion_point(message_clear_start:tutorial.Persion)
  if (has_name()) {
    GOOGLE_DCHECK(!name_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
    (*name_.UnsafeRawStringPointer())->clear();
  }
  age_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool Persion::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:tutorial.Persion)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->name().data(), static_cast<int>(this->name().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "tutorial.Persion.name");
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 age = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u)) {
          set_has_age();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &age_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:tutorial.Persion)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:tutorial.Persion)
  return false;
#undef DO_
}

void Persion::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:tutorial.Persion)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "tutorial.Persion.name");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->name(), output);
  }

  // required int32 age = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->age(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:tutorial.Persion)
}

::google::protobuf::uint8* Persion::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:tutorial.Persion)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required string name = 1;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->name().data(), static_cast<int>(this->name().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "tutorial.Persion.name");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }

  // required int32 age = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->age(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tutorial.Persion)
  return target;
}

size_t Persion::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:tutorial.Persion)
  size_t total_size = 0;

  if (has_name()) {
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());
  }

  if (has_age()) {
    // required int32 age = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->age());
  }

  return total_size;
}
size_t Persion::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tutorial.Persion)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required string name = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->name());

    // required int32 age = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->age());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Persion::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:tutorial.Persion)
  GOOGLE_DCHECK_NE(&from, this);
  const Persion* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const Persion>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:tutorial.Persion)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:tutorial.Persion)
    MergeFrom(*source);
  }
}

void Persion::MergeFrom(const Persion& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:tutorial.Persion)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 3u) {
    if (cached_has_bits & 0x00000001u) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (cached_has_bits & 0x00000002u) {
      age_ = from.age_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Persion::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:tutorial.Persion)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Persion::CopyFrom(const Persion& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tutorial.Persion)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Persion::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void Persion::Swap(Persion* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Persion::InternalSwap(Persion* other) {
  name_.Swap(&other->name_);
  std::swap(age_, other->age_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata Persion::GetMetadata() const {
  protobuf_addressbook_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_addressbook_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// Persion

// required string name = 1;
bool Persion::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void Persion::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
void Persion::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
void Persion::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
const ::std::string& Persion::name() const {
  // @@protoc_insertion_point(field_get:tutorial.Persion.name)
  return name_.GetNoArena();
}
void Persion::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial.Persion.name)
}
#if LANG_CXX11
void Persion::set_name(::std::string&& value) {
  set_has_name();
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial.Persion.name)
}
#endif
void Persion::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial.Persion.name)
}
void Persion::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial.Persion.name)
}
::std::string* Persion::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:tutorial.Persion.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* Persion::release_name() {
  // @@protoc_insertion_point(field_release:tutorial.Persion.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void Persion::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tutorial.Persion.name)
}

// required int32 age = 2;
bool Persion::has_age() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void Persion::set_has_age() {
  _has_bits_[0] |= 0x00000002u;
}
void Persion::clear_has_age() {
  _has_bits_[0] &= ~0x00000002u;
}
void Persion::clear_age() {
  age_ = 0;
  clear_has_age();
}
::google::protobuf::int32 Persion::age() const {
  // @@protoc_insertion_point(field_get:tutorial.Persion.age)
  return age_;
}
void Persion::set_age(::google::protobuf::int32 value) {
  set_has_age();
  age_ = value;
  // @@protoc_insertion_point(field_set:tutorial.Persion.age)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int AddressBook::kPersionFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

AddressBook::AddressBook()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_addressbook_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:tutorial.AddressBook)
}
AddressBook::AddressBook(const AddressBook& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      persion_(from.persion_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:tutorial.AddressBook)
}

void AddressBook::SharedCtor() {
  _cached_size_ = 0;
}

AddressBook::~AddressBook() {
  // @@protoc_insertion_point(destructor:tutorial.AddressBook)
  SharedDtor();
}

void AddressBook::SharedDtor() {
}

void AddressBook::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AddressBook::descriptor() {
  protobuf_addressbook_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_addressbook_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const AddressBook& AddressBook::default_instance() {
  protobuf_addressbook_2eproto::InitDefaults();
  return *internal_default_instance();
}

AddressBook* AddressBook::New(::google::protobuf::Arena* arena) const {
  AddressBook* n = new AddressBook;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void AddressBook::Clear() {
// @@protoc_insertion_point(message_clear_start:tutorial.AddressBook)
  persion_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool AddressBook::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:tutorial.AddressBook)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .tutorial.Persion persion = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_persion()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:tutorial.AddressBook)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:tutorial.AddressBook)
  return false;
#undef DO_
}

void AddressBook::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:tutorial.AddressBook)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .tutorial.Persion persion = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->persion_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->persion(static_cast<int>(i)), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:tutorial.AddressBook)
}

::google::protobuf::uint8* AddressBook::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:tutorial.AddressBook)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .tutorial.Persion persion = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->persion_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, this->persion(static_cast<int>(i)), deterministic, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:tutorial.AddressBook)
  return target;
}

size_t AddressBook::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:tutorial.AddressBook)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // repeated .tutorial.Persion persion = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->persion_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->persion(static_cast<int>(i)));
    }
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AddressBook::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:tutorial.AddressBook)
  GOOGLE_DCHECK_NE(&from, this);
  const AddressBook* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const AddressBook>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:tutorial.AddressBook)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:tutorial.AddressBook)
    MergeFrom(*source);
  }
}

void AddressBook::MergeFrom(const AddressBook& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:tutorial.AddressBook)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  persion_.MergeFrom(from.persion_);
}

void AddressBook::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:tutorial.AddressBook)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AddressBook::CopyFrom(const AddressBook& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:tutorial.AddressBook)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AddressBook::IsInitialized() const {
  if (!::google::protobuf::internal::AllAreInitialized(this->persion())) return false;
  return true;
}

void AddressBook::Swap(AddressBook* other) {
  if (other == this) return;
  InternalSwap(other);
}
void AddressBook::InternalSwap(AddressBook* other) {
  persion_.InternalSwap(&other->persion_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata AddressBook::GetMetadata() const {
  protobuf_addressbook_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_addressbook_2eproto::file_level_metadata[kIndexInFileMessages];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// AddressBook

// repeated .tutorial.Persion persion = 1;
int AddressBook::persion_size() const {
  return persion_.size();
}
void AddressBook::clear_persion() {
  persion_.Clear();
}
const ::tutorial::Persion& AddressBook::persion(int index) const {
  // @@protoc_insertion_point(field_get:tutorial.AddressBook.persion)
  return persion_.Get(index);
}
::tutorial::Persion* AddressBook::mutable_persion(int index) {
  // @@protoc_insertion_point(field_mutable:tutorial.AddressBook.persion)
  return persion_.Mutable(index);
}
::tutorial::Persion* AddressBook::add_persion() {
  // @@protoc_insertion_point(field_add:tutorial.AddressBook.persion)
  return persion_.Add();
}
::google::protobuf::RepeatedPtrField< ::tutorial::Persion >*
AddressBook::mutable_persion() {
  // @@protoc_insertion_point(field_mutable_list:tutorial.AddressBook.persion)
  return &persion_;
}
const ::google::protobuf::RepeatedPtrField< ::tutorial::Persion >&
AddressBook::persion() const {
  // @@protoc_insertion_point(field_list:tutorial.AddressBook.persion)
  return persion_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace tutorial

// @@protoc_insertion_point(global_scope)
