// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_EXAMPLES_EXAMPLES_WINDOW_H_
#define UI_VIEWS_EXAMPLES_EXAMPLES_WINDOW_H_

#include <memory>
#include <vector>

#include "my_example_base.h"

#include "ui/gfx/native_widget_types.h"
#include "ui/views/examples/views_examples_export.h"

namespace mysrc {


// Shows a window with the views examples in it. |extra_examples| contains any
// additional examples to add. |window_context| is used to determine where the
// window should be created (see |Widget::InitParams::context| for details).
void ShowExamplesWindow(
    base::OnceClosure on_close,
    gfx::NativeWindow window_context = nullptr,
    std::vector<std::unique_ptr<ExampleBase>> extra_examples =
        std::vector<std::unique_ptr<ExampleBase>>());


}  // namespace mysrc

#endif  // UI_VIEWS_EXAMPLES_EXAMPLES_WINDOW_H_
