// Copyright 2014 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/compiler/access-builder.h"
#include "src/types-inl.h"

namespace v8 {
namespace internal {
namespace compiler {

// static
FieldAccess AccessBuilder::ForMap() {
  return {kTaggedBase, HeapObject::kMapOffset, MaybeHandle<Name>(), Type::Any(),
          kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForJSObjectProperties() {
  return {kTaggedBase, JSObject::kPropertiesOffset, MaybeHandle<Name>(),
          Type::Any(), kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForJSObjectElements() {
  return {kTaggedBase, JSObject::kElementsOffset, MaybeHandle<Name>(),
          Type::Internal(), kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForJSFunctionContext() {
  return {kTaggedBase, JSFunction::kContextOffset, MaybeHandle<Name>(),
          Type::Internal(), kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForJSArrayBufferBackingStore() {
  return {kTaggedBase, JSArrayBuffer::kBackingStoreOffset, MaybeHandle<Name>(),
          Type::UntaggedPointer(), kMachPtr};
}


// static
FieldAccess AccessBuilder::ForExternalArrayPointer() {
  return {kTaggedBase, ExternalArray::kExternalPointerOffset,
          MaybeHandle<Name>(), Type::UntaggedPointer(), kMachPtr};
}


// static
FieldAccess AccessBuilder::ForMapInstanceType() {
  return {kTaggedBase, Map::kInstanceTypeOffset, Handle<Name>(),
          Type::UntaggedUnsigned8(), kMachUint8};
}


// static
FieldAccess AccessBuilder::ForStringLength(Zone* zone) {
  return {kTaggedBase, String::kLengthOffset, Handle<Name>(),
          Type::Range(0, String::kMaxLength, zone), kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForValue() {
  return {kTaggedBase, JSValue::kValueOffset, Handle<Name>(), Type::Any(),
          kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForContextSlot(size_t index) {
  int offset = Context::kHeaderSize + static_cast<int>(index) * kPointerSize;
  DCHECK_EQ(offset,
            Context::SlotOffset(static_cast<int>(index)) + kHeapObjectTag);
  return {kTaggedBase, offset, Handle<Name>(), Type::Any(), kMachAnyTagged};
}


// static
FieldAccess AccessBuilder::ForStatsCounter() {
  return {kUntaggedBase, 0, MaybeHandle<Name>(), Type::Signed32(), kMachInt32};
}


// static
FieldAccess AccessBuilder::ForPropertyCellValue() {
  return {kTaggedBase, PropertyCell::kValueOffset, Handle<Name>(), Type::Any(),
          kMachAnyTagged};
}


// static
ElementAccess AccessBuilder::ForFixedArrayElement() {
  return {kTaggedBase, FixedArray::kHeaderSize, Type::Any(), kMachAnyTagged};
}


// static
ElementAccess AccessBuilder::ForTypedArrayElement(ExternalArrayType type,
                                                  bool is_external) {
  BaseTaggedness taggedness = is_external ? kUntaggedBase : kTaggedBase;
  int header_size = is_external ? 0 : FixedTypedArrayBase::kDataOffset;
  switch (type) {
    case kExternalInt8Array:
      return {taggedness, header_size, Type::Signed32(), kMachInt8};
    case kExternalUint8Array:
    case kExternalUint8ClampedArray:
      return {taggedness, header_size, Type::Unsigned32(), kMachUint8};
    case kExternalInt16Array:
      return {taggedness, header_size, Type::Signed32(), kMachInt16};
    case kExternalUint16Array:
      return {taggedness, header_size, Type::Unsigned32(), kMachUint16};
    case kExternalInt32Array:
      return {taggedness, header_size, Type::Signed32(), kMachInt32};
    case kExternalUint32Array:
      return {taggedness, header_size, Type::Unsigned32(), kMachUint32};
    case kExternalFloat32Array:
      return {taggedness, header_size, Type::Number(), kMachFloat32};
    case kExternalFloat64Array:
      return {taggedness, header_size, Type::Number(), kMachFloat64};
    case kExternalFloat32x4Array:
    case kExternalInt32x4Array:
    case kExternalFloat64x2Array:
      // TODO(ningxin): fix this workaround.
      return {kUntaggedBase, 0, Type::None(), kMachNone};
  }
  UNREACHABLE();
  return {kUntaggedBase, 0, Type::None(), kMachNone};
}


// static
ElementAccess AccessBuilder::ForSeqStringChar(String::Encoding encoding) {
  switch (encoding) {
    case String::ONE_BYTE_ENCODING:
      return {kTaggedBase, SeqString::kHeaderSize, Type::Unsigned32(),
              kMachUint8};
    case String::TWO_BYTE_ENCODING:
      return {kTaggedBase, SeqString::kHeaderSize, Type::Unsigned32(),
              kMachUint16};
  }
  UNREACHABLE();
  return {kUntaggedBase, 0, Type::None(), kMachNone};
}

}  // namespace compiler
}  // namespace internal
}  // namespace v8
