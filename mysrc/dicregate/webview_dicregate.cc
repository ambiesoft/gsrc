// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "webview_dicregate.h"

#include <memory>

#include "content/public/browser/browser_context.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/controls/webview/webview.h"
#include "ui/views/layout/fill_layout.h"

using views::FillLayout;

namespace ambiesoft {
namespace dicregate {

WebViewDicregate::WebViewDicregate(content::BrowserContext* browser_context)
    : webview_(nullptr), browser_context_(browser_context) {}

WebViewDicregate::~WebViewDicregate() = default;

void WebViewDicregate::CreateDicregateView() {
  webview_ = new views::WebView(browser_context_);
  webview_->GetWebContents()->SetDelegate(this);
  SetLayoutManager(std::make_unique<FillLayout>());
  AddChildView(webview_);

  webview_->LoadInitialURL(GURL("http://www.google.com/"));
  webview_->GetWebContents()->Focus();
}

bool WebViewDicregate::HandleKeyboardEvent(
    content::WebContents* source,
    const content::NativeWebKeyboardEvent& event) {
  return unhandled_keyboard_event_handler_.HandleKeyboardEvent(
      event, webview_->GetFocusManager());
}

}  // namespace dicregate
}  // namespace ambiesoft
