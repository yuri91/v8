// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_WASM_BRANCH_HINT_MAP_H_
#define V8_WASM_BRANCH_HINT_MAP_H_

#include <unordered_map>

namespace v8 {
namespace internal {

namespace wasm {

enum class WasmBranchHintDirection : uint8_t {
  kNoHint = 0,
  kFalse = 1,
  kTrue = 2,
};

// Static representation of a wasm branch hint
struct WasmBranchHint {
  WasmBranchHintDirection direction;
};


class V8_EXPORT_PRIVATE BranchHintMap {
 public:
   void insert(uint32_t offset, WasmBranchHint hint) {
     map_.emplace(offset, hint);
   }
   WasmBranchHint GetHintFor(uint32_t offset) const {
     auto it = map_.find(offset);
     if(it == map_.end()) {
       return WasmBranchHint{WasmBranchHintDirection::kNoHint};
     }
     return it->second;
   }
 private:
  std::unordered_map<uint32_t, WasmBranchHint> map_;
};

using BranchHintInfo = std::unordered_map<uint32_t, BranchHintMap>;

}  // namespace wasm
}  // namespace internal
}  // namespace v8

#endif  // V8_WASM_SIGNATURE_MAP_H_
