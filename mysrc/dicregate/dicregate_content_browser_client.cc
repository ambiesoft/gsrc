// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_browser_client.h"
#include "dicregate_content_client_main_parts.h"

#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"


namespace ambiesoft {
namespace dicregate {

DicregateContentBrowserClient::DicregateContentBrowserClient(
    DicregateContentClient* dicregate_content_client)
    : dicregate_content_client_(dicregate_content_client) {}

DicregateContentBrowserClient::~DicregateContentBrowserClient() {}

std::unique_ptr<content::BrowserMainParts>
DicregateContentBrowserClient::CreateBrowserMainParts(
    const content::MainFunctionParams& parameters) {
  return DicregateContentClientMainParts::Create(parameters,
                                             dicregate_content_client_);
}

}  // namespace dicregate
}  // namespace ambiesoft
