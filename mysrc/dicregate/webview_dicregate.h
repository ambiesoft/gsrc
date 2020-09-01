// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_WEBVIEW_DICREGATE_H_
#define AMBIESOFT_WEBVIEW_DICREGATE_H_

#include "base/macros.h"
#include "content/public/browser/web_contents_delegate.h"
#include "ui/views/controls/webview/unhandled_keyboard_event_handler.h"
#include "ui/views/view.h"

namespace content {
class BrowserContext;
}

namespace views {
class WebView;
}

namespace ambiesoft {
namespace dicregate {

class WebViewDicregate : public content::WebContentsDelegate, public views::View {
 public:
  explicit WebViewDicregate(content::BrowserContext* browser_context);
  ~WebViewDicregate() override;

  void CreateDicregateView() ;

  // content::WebContentsDelegate:
  bool HandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event) override;

 private:
  views::WebView* webview_;
  content::BrowserContext* browser_context_;
  views::UnhandledKeyboardEventHandler unhandled_keyboard_event_handler_;

  DISALLOW_COPY_AND_ASSIGN(WebViewDicregate);
};

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // AMBIESOFT_WEBVIEW_DICREGATE_H_
