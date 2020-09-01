// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_client_main_parts.h"
#include "dicregate_content_client.h"

#include <utility>

#include "base/run_loop.h"
#include "build/build_config.h"
#include "content/shell/browser/shell_browser_context.h"
#include "ui/base/ime/init/input_method_initializer.h"
#include "ui/views/test/desktop_test_views_delegate.h"


namespace ambiesoft {
namespace dicregate {

DicregateContentClientMainParts::DicregateContentClientMainParts(
    const content::MainFunctionParams& content_params,
    DicregateContentClient* dicregate_content_client)
    : dicregate_content_client_(dicregate_content_client) {}

DicregateContentClientMainParts::~DicregateContentClientMainParts() {}

#if !defined(OS_MACOSX)
void DicregateContentClientMainParts::PreCreateMainMessageLoop() {}
#endif

void DicregateContentClientMainParts::PreMainMessageLoopRun() {
  ui::InitializeInputMethodForTesting();
  browser_context_ = std::make_unique<content::ShellBrowserContext>(false);

  views_delegate_ = std::make_unique<views::DesktopTestViewsDelegate>();
  run_loop_ = std::make_unique<base::RunLoop>();
  dicregate_content_client()->set_quit_closure(run_loop_->QuitClosure());
}

void DicregateContentClientMainParts::PostMainMessageLoopRun() {
  browser_context_.reset();
  views_delegate_.reset();
}

bool DicregateContentClientMainParts::MainMessageLoopRun(int* result_code) {
  run_loop_->Run();
  return true;
}

}  // namespace dicregate
}  // namespace ambiesoft
