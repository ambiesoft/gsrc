// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DICREGATE_CONTENT_MAIN_DELEGATE_H_
#define DICREGATE_CONTENT_MAIN_DELEGATE_H_

#include "dicregate_content_client.h"

#include <memory>

#include "base/macros.h"
#include "content/public/app/content_main_delegate.h"
#include "ui/views_content_client/views_content_browser_client.h"




namespace ambiesoft {
namespace dicregate {

class DicregateContentBrowserClient;

class DicregateContentMainDelegate : public content::ContentMainDelegate {
 public:
  explicit DicregateContentMainDelegate(
      DicregateContentClient* dicregate_content_client);
  ~DicregateContentMainDelegate() override;

  // content::ContentMainDelegate implementation
  bool BasicStartupComplete(int* exit_code) override;
  void PreSandboxStartup() override;
  void PreCreateMainMessageLoop() override;
  content::ContentClient* CreateContentClient() override;
  content::ContentBrowserClient* CreateContentBrowserClient() override;

 private:
  std::unique_ptr<DicregateContentBrowserClient> browser_client_;
  DicregateContentClient* dicregate_content_client_;

  DISALLOW_COPY_AND_ASSIGN(DicregateContentMainDelegate);
};

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // DICREGATE_CONTENT_MAIN_DELEGATE_H_
