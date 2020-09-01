// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DICREGATE_CONTENT_BROWSER_CLIENT_H_
#define DICREGATE_CONTENT_BROWSER_CLIENT_H_


#include <memory>

#include "base/macros.h"
#include "content/public/browser/content_browser_client.h"

namespace ambiesoft {
namespace dicregate {

class DicregateContentClient;

class DicregateContentBrowserClient : public content::ContentBrowserClient {
 public:
  explicit DicregateContentBrowserClient(
      DicregateContentClient* views_content_client);
  ~DicregateContentBrowserClient() override;

  // content::ContentBrowserClient:
  std::unique_ptr<content::BrowserMainParts> CreateBrowserMainParts(
      const content::MainFunctionParams& parameters) override;

 private:
  DicregateContentClient* dicregate_content_client_;

  DISALLOW_COPY_AND_ASSIGN(DicregateContentBrowserClient);
};

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // DICREGATE_CONTENT_BROWSER_CLIENT_H_
