// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_client_main_parts_aura.h"

#include "ui/wm/core/wm_state.h"

namespace ambiesoft {
namespace dicregate {

DicregateContentClientMainPartsAura::DicregateContentClientMainPartsAura(
    const content::MainFunctionParams& content_params,
    DicregateContentClient* views_content_client)
    : DicregateContentClientMainParts(content_params, views_content_client) {}

DicregateContentClientMainPartsAura::~DicregateContentClientMainPartsAura() {}

void DicregateContentClientMainPartsAura::ToolkitInitialized() {
  DicregateContentClientMainParts::ToolkitInitialized();

  wm_state_ = std::make_unique<::wm::WMState>();
}

void DicregateContentClientMainPartsAura::PostMainMessageLoopRun() {
  DicregateContentClientMainParts::PostMainMessageLoopRun();
}

}  // namespace dicregate
}  // namespace ambiesoft
