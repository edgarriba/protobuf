// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "google/protobuf/compiler/cpp/file.h"

#include <cstddef>
#include <vector>

#include "google/protobuf/testing/googletest.h"
#include <gtest/gtest.h>
#include "absl/strings/match.h"
#include "absl/strings/string_view.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/unittest.pb.h"

// Must be included last.
#include "google/protobuf/port_def.inc"

namespace google {
namespace protobuf {
namespace compiler {
namespace cpp {

class FileGeneratorFriendForTesting {
 public:
  static std::vector<const Descriptor*> MessagesInTopologicalOrder(
      const FileGenerator& fgen) {
    return fgen.MessagesInTopologicalOrder();
  }
};

namespace {
// Test that the descriptors are ordered in a topological order.
TEST(FileTest, TopologicallyOrderedDescriptors) {
  const FileDescriptor* fdesc =
      protobuf_unittest::TestAllTypes::descriptor()->file();
  FileGenerator fgen(fdesc, /*options=*/{});
  static constexpr absl::string_view kExpectedDescriptorOrder[] = {
      "Uint64Message",
      "Uint32Message",
      "TestVerifyUint32Simple",
      "TestVerifyInt32Simple",
      "TestVerifyBigFieldNumberUint32.Nested",
      "TestUnpackedTypes",
      "TestUnpackedExtensions",
      "TestReservedFields",
      "TestRequiredOneof.NestedMessage",
      "TestRequiredEnum",
      "TestRepeatedString",
      "TestRepeatedScalarDifferentTagSizes",
      "TestRecursiveMessage",
      "TestReallyLargeTagNumber",
      "TestPickleNestedMessage.NestedMessage.NestedNestedMessage",
      "TestPickleNestedMessage.NestedMessage",
      "TestPickleNestedMessage",
      "TestPackedTypes",
      "TestPackedExtensions",
      "TestPackedEnumSmallRange",
      "TestOneofBackwardsCompatible.FooGroup",
      "TestOneof2.NestedMessage",
      "TestOneof2.FooGroup",
      "TestOneof.FooGroup",
      "TestNestedMessageRedaction",
      "TestNestedGroupExtensionOuter.Layer1OptionalGroup.Layer2RepeatedGroup",
      "TestNestedGroupExtensionOuter.Layer1OptionalGroup."
      "Layer2AnotherOptionalRepeatedGroup",
      "TestNestedGroupExtensionInnerExtension",
      "TestNestedExtension.OptionalGroup_extension",
      "TestNestedExtension",
      "TestMultipleExtensionRanges",
      "TestMixedFieldsAndExtensions",
      "TestMessageSize",
      "TestJsonName",
      "TestIsInitialized.SubMessage.SubGroup",
      "TestHugeFieldNumbers.StringStringMapEntry",
      "TestHugeFieldNumbers.OptionalGroup",
      "TestGroupExtension",
      "TestGroup.OptionalGroup",
      "TestFieldOrderings.NestedMessage",
      "TestExtremeDefaultValues",
      "TestExtensionRangeSerialize",
      "TestExtensionOrderings2.TestExtensionOrderings3",
      "TestExtensionOrderings2",
      "TestExtensionOrderings1",
      "TestExtensionInsideTable",
      "TestEmptyMessageWithExtensions",
      "TestEmptyMessage",
      "TestDynamicExtensions.DynamicMessageType",
      "TestDupFieldNumber.Foo",
      "TestDupFieldNumber.Bar",
      "TestDeprecatedMessage",
      "TestCord",
      "TestCommentInjectionMessage",
      "TestChildExtensionData.NestedTestAllExtensionsData."
      "NestedDynamicExtensions",
      "TestAllTypes.RepeatedGroup",
      "TestAllTypes.OptionalGroup",
      "TestAllTypes.NestedMessage",
      "TestAllExtensions",
      "StringParseTester",
      "SparseEnumMessage",
      "RepeatedGroup_extension",
      "RedactedFields.MapUnredactedStringEntry",
      "RedactedFields.MapRedactedStringEntry",
      "OptionalGroup_extension",
      "OneString",
      "OneBytes",
      "MoreString",
      "MoreBytes",
      "ManyOptionalString",
      "Int64ParseTester",
      "Int64Message",
      "Int32ParseTester",
      "Int32Message",
      "InlinedStringIdxRegressionProto",
      "ForeignMessage",
      "FooServerMessage",
      "FooResponse",
      "FooRequest",
      "FooClientMessage",
      "EnumsForBenchmark",
      "EnumParseTester",
      "BoolParseTester",
      "BoolMessage",
      "BarResponse",
      "BarRequest",
      "BadFieldNames",
      "TestVerifyBigFieldNumberUint32",
      "TestRequiredOneof",
      "TestRequired",
      "TestOneof2",
      "TestNestedMessageHasBits.NestedMessage",
      "TestNestedGroupExtensionOuter.Layer1OptionalGroup",
      "TestMergeException",
      "TestIsInitialized.SubMessage",
      "TestGroup",
      "TestForeignNested",
      "TestFieldOrderings",
      "TestEagerMaybeLazy.NestedMessage",
      "TestDynamicExtensions",
      "TestDupFieldNumber",
      "TestDeprecatedFields",
      "TestChildExtensionData.NestedTestAllExtensionsData",
      "TestChildExtension",
      "TestCamelCaseFieldNames",
      "TestAllTypes",
      "RedactedFields",
      "TestVerifyUint32BigFieldNumber",
      "TestVerifyUint32",
      "TestVerifyOneUint32",
      "TestVerifyOneInt32BigFieldNumber",
      "TestVerifyMostlyInt32BigFieldNumber",
      "TestVerifyMostlyInt32",
      "TestVerifyInt32BigFieldNumber",
      "TestVerifyInt32",
      "TestRequiredMessage",
      "TestParsingMerge.RepeatedGroup",
      "TestParsingMerge.RepeatedFieldsGenerator.Group2",
      "TestParsingMerge.RepeatedFieldsGenerator.Group1",
      "TestParsingMerge.OptionalGroup",
      "TestOneofBackwardsCompatible",
      "TestOneof",
      "TestNestedMessageHasBits",
      "TestNestedGroupExtensionOuter",
      "TestNestedChildExtension",
      "TestMutualRecursionA.SubGroupR",
      "TestLazyMessage",
      "TestIsInitialized",
      "TestHugeFieldNumbers",
      "TestEagerMessage",
      "TestEagerMaybeLazy",
      "TestChildExtensionData",
      "NestedTestAllTypes",
      "TestRequiredForeign",
      "TestParsingMerge.RepeatedFieldsGenerator",
      "TestParsingMerge",
      "TestNestedChildExtensionData",
      "TestMutualRecursionA",
      "TestMutualRecursionA.SubGroup",
      "TestMutualRecursionA.SubMessage",
      "TestMutualRecursionB",
      "TestLazyMessageRepeated",
      "TestNestedRequiredForeign",
  };
  static constexpr size_t kExpectedDescriptorCount =
      std::end(kExpectedDescriptorOrder) - std::begin(kExpectedDescriptorOrder);
  std::vector<const Descriptor*> actual_descriptor_order =
      FileGeneratorFriendForTesting::MessagesInTopologicalOrder(fgen);
  EXPECT_TRUE(kExpectedDescriptorCount == actual_descriptor_order.size())
      << "Expected: " << kExpectedDescriptorCount
      << ", got: " << actual_descriptor_order.size();
  for (size_t i = 0; i < actual_descriptor_order.size(); ++i) {
    bool found = false;
    const Descriptor* desc = actual_descriptor_order[i];
    for (size_t j = 0; j < kExpectedDescriptorCount; ++j) {
      if (absl::EndsWith(desc->full_name(), kExpectedDescriptorOrder[j])) {
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found) << "Descriptor " << desc->full_name() << " not found!";
  }
}

}  // namespace
}  // namespace cpp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google
