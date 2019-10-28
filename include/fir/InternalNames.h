// Copyright (c) 2019, NVIDIA CORPORATION.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FIR_INTERNAL_NAMES_H
#define FIR_INTERNAL_NAMES_H

#include "llvm/ADT/StringSet.h"
#include <cstdint>

namespace llvm {
template <typename>
class ArrayRef;
template <typename>
class Optional;
class Twine;
} // namespace llvm

namespace fir {

/// Internal name mangling of identifiers
struct NameMangler {
  enum class IntrinsicType { CHARACTER, COMPLEX, INTEGER, LOGICAL, REAL };

  NameMangler();

  /// Mangle a common block name
  llvm::Twine doCommonBlock(llvm::StringRef name);

  /// Mangle a (global) constant name
  llvm::Twine doConstant(llvm::ArrayRef<llvm::StringRef> modules,
                         llvm::StringRef name);

  /// Mangle a dispatch table name
  llvm::Twine doDispatchTable(llvm::ArrayRef<llvm::StringRef> modules,
                              llvm::Optional<llvm::StringRef> host,
                              llvm::StringRef name,
                              llvm::ArrayRef<std::int64_t> kinds);

  /// Mangle a compiler generated name
  llvm::Twine doGenerated(llvm::StringRef name);

  /// Mangle an intrinsic type descriptor
  llvm::Twine doIntrinsicTypeDescriptor(llvm::ArrayRef<llvm::StringRef> modules,
                                        llvm::Optional<llvm::StringRef> host,
                                        IntrinsicType type, std::int64_t kind);

  /// Mangle a procedure name
  llvm::Twine doProcedure(llvm::ArrayRef<llvm::StringRef> modules,
                          llvm::Optional<llvm::StringRef> host,
                          llvm::StringRef name);

  /// Mangle a derived type name
  llvm::Twine doType(llvm::ArrayRef<llvm::StringRef> modules,
                     llvm::Optional<llvm::StringRef> host, llvm::StringRef name,
                     llvm::ArrayRef<std::int64_t> kinds);

  /// Mangle a (derived) type descriptor name
  llvm::Twine doTypeDescriptor(llvm::ArrayRef<llvm::StringRef> modules,
                               llvm::Optional<llvm::StringRef> host,
                               llvm::StringRef name,
                               llvm::ArrayRef<std::int64_t> kinds);

  /// Mangle a (global) variable name
  llvm::Twine doVariable(llvm::ArrayRef<llvm::StringRef> modules,
                         llvm::StringRef name);

private:
  llvm::Twine addAsString(std::int64_t i);
  llvm::Twine doKind(std::int64_t kind);
  llvm::Twine doKinds(llvm::ArrayRef<std::int64_t> kinds);
  llvm::Twine toLower(llvm::StringRef name);

  llvm::StringSet<> cache;
};

} // namespace fir

#endif // FIR_INTERNAL_NAMES_H
