// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_DICREGATE_CONTENT_H_
#define AMBIESOFT_DICREGATE_CONTENT_H_

#include "base/callback_forward.h"
#include "ui/gfx/native_widget_types.h"

namespace content {
class BrowserContext;
}

namespace ambiesoft {
namespace dicregate {

void ShowDicregateContent(
    base::OnceClosure on_close,
    content::BrowserContext* browser_context,
    gfx::NativeWindow window_context);

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // AMBIESOFT_DICREGATE_CONTENT_H_
