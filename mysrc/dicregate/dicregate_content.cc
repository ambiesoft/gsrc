// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content.h"
#include "dicregate_window.h"
#include <memory>
#include <utility>
#include <vector>

#include "content/public/browser/browser_context.h"
// #include "ui/views/examples/create_examples.h"
// #include "ui/views/examples/example_base.h"
#include "webview_dicregate.h"

namespace ambiesoft {
namespace dicregate {

void ShowDicregateContent(base::OnceClosure on_close,
                                   content::BrowserContext* browser_context,
                                   gfx::NativeWindow window_context) {
  auto webviewDicregate = std::make_unique<WebViewDicregate>(browser_context);
  ShowDicregateWindow(std::move(on_close), std::move(webviewDicregate),
                     window_context);
}

}  // namespace dicregate
}  // namespace ambiesoft
