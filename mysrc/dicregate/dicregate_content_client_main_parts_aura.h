// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DICREGATE_CONTENT_CLIENT_MAIN_PARTS_AURA_H_
#define DICREGATE_CONTENT_CLIENT_MAIN_PARTS_AURA_H_

#include <memory>

#include "base/macros.h"
#include "dicregate_content_client.h"
#include "dicregate_content_client_main_parts.h"

namespace wm {
class WMState;
}

namespace ambiesoft {
namespace dicregate {

class DicregateContentClientMainPartsAura : public DicregateContentClientMainParts {
 protected:
  DicregateContentClientMainPartsAura(
      const content::MainFunctionParams& content_params,
      DicregateContentClient* dicregate_content_client);
  ~DicregateContentClientMainPartsAura() override;

  // content::BrowserMainParts:
  void ToolkitInitialized() override;
  void PostMainMessageLoopRun() override;

 private:
  std::unique_ptr<::wm::WMState> wm_state_;

  DISALLOW_COPY_AND_ASSIGN(DicregateContentClientMainPartsAura);
};

}  // namespace dicregate
}  // namespace ambiesoft
#endif  // DICREGATE_CONTENT_CLIENT_MAIN_PARTS_AURA_H_
