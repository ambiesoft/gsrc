// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_client_main_parts_aura.h"
#include "dicregate_content_client.h"

#include "content/shell/browser/shell_browser_context.h"
#include "ui/display/screen.h"
#include "ui/views/widget/desktop_aura/desktop_screen.h"



namespace ambiesoft {
namespace dicregate {

namespace {

class DicregateContentClientMainPartsDesktopAura
    : public DicregateContentClientMainPartsAura {
 public:
  DicregateContentClientMainPartsDesktopAura(
      const content::MainFunctionParams& content_params,
      DicregateContentClient* dicregate_content_client);
  DicregateContentClientMainPartsDesktopAura(
      const DicregateContentClientMainPartsDesktopAura&) = delete;
  DicregateContentClientMainPartsDesktopAura& operator=(
      const DicregateContentClientMainPartsDesktopAura&) = delete;
  ~DicregateContentClientMainPartsDesktopAura() override = default;

  // DicregateContentClientMainPartsAura:
  void PreMainMessageLoopRun() override;
};

DicregateContentClientMainPartsDesktopAura::
    DicregateContentClientMainPartsDesktopAura(
        const content::MainFunctionParams& content_params,
        DicregateContentClient* dicregate_content_client)
    : DicregateContentClientMainPartsAura(content_params,
                                          dicregate_content_client) {}

void DicregateContentClientMainPartsDesktopAura::PreMainMessageLoopRun() {
  DicregateContentClientMainPartsAura::PreMainMessageLoopRun();

  views::CreateDesktopScreen();

  dicregate_content_client()->OnPreMainMessageLoopRun(browser_context(),
                                                      nullptr);
}

}  // namespace

// static
std::unique_ptr<DicregateContentClientMainParts>
DicregateContentClientMainParts::Create(
    const content::MainFunctionParams& content_params,
    DicregateContentClient* dicregate_content_client) {
  return std::make_unique<DicregateContentClientMainPartsDesktopAura>(
      content_params, dicregate_content_client);
}

}  // namespace dicregate
}  // namespace ambiesoft