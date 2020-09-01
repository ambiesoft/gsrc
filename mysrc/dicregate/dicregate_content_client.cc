// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_client.h"
#include "dicregate_content_main_delegate.h"

#include <utility>

#include "build/build_config.h"
#include "content/public/app/content_main.h"
#include "ui/views_content_client/views_content_main_delegate.h"

namespace ambiesoft {
namespace dicregate {

#if defined(OS_WIN)
DicregateContentClient::DicregateContentClient(
    HINSTANCE instance,
    sandbox::SandboxInterfaceInfo* sandbox_info)
    : instance_(instance), sandbox_info_(sandbox_info) {}
#else
DicregateContentClient::DicregateContentClient(int argc, const char** argv)
    : argc_(argc), argv_(argv) {}
#endif

DicregateContentClient::~DicregateContentClient() {}


void DicregateContentClient::OnPreMainMessageLoopRun(
    content::BrowserContext* browser_context,
    gfx::NativeWindow window_context) {
  std::move(on_pre_main_message_loop_run_callback_)
      .Run(browser_context, window_context);
}

void DicregateContentClient::OnResourcesLoaded() {
  if (on_resources_loaded_callback_)
    std::move(on_resources_loaded_callback_).Run();
}

}  // namespace dicregate
}  // namespace ambiesoft
