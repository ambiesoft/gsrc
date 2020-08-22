// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DICREGATE_CONTENT_CLIENT_MAIN_PARTS_H_
#define DICREGATE_CONTENT_CLIENT_MAIN_PARTS_H_

#include <memory>

#include "base/macros.h"
#include "build/build_config.h"
#include "content/public/browser/browser_main_parts.h"

namespace base {
class RunLoop;
}

namespace content {
class ShellBrowserContext;
struct MainFunctionParams;
}

namespace views {
class TestViewsDelegate;
}

namespace ambiesoft {
namespace dicregate {

class DicregateContentClient;

class DicregateContentClientMainParts : public content::BrowserMainParts {
 public:
  // Platform-specific create function.
  static std::unique_ptr<DicregateContentClientMainParts> Create(
      const content::MainFunctionParams& content_params,
      DicregateContentClient* dicregate_content_client);

  // Invoked before the BrowserMainLoop constructor.
  static void PreCreateMainMessageLoop();

  ~DicregateContentClientMainParts() override;

  // content::BrowserMainParts:
  void PreMainMessageLoopRun() override;
  bool MainMessageLoopRun(int* result_code) override;
  void PostMainMessageLoopRun() override;

  content::ShellBrowserContext* browser_context() {
    return browser_context_.get();
  }

  DicregateContentClient* dicregate_content_client() { return dicregate_content_client_; }

 protected:
  DicregateContentClientMainParts(const content::MainFunctionParams& content_params,
                              DicregateContentClient* dicregate_content_client);

#if defined(OS_MACOSX)
  views::TestViewsDelegate* views_delegate() { return views_delegate_.get(); }
#endif

 private:
  std::unique_ptr<content::ShellBrowserContext> browser_context_;

  std::unique_ptr<views::TestViewsDelegate> views_delegate_;

  DicregateContentClient* dicregate_content_client_;

  std::unique_ptr<base::RunLoop> run_loop_;

  DISALLOW_COPY_AND_ASSIGN(DicregateContentClientMainParts);
};

}  // namespace dicregate
}  // namespace ambiesoft
#endif  // DICREGATE_CONTENT_CLIENT_MAIN_PARTS_H_
