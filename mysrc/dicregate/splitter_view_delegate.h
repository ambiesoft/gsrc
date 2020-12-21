// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_SPLITTER_VIEW_DELEGATE_H_
#define AMBIESOFT_SPLITTER_VIEW_DELEGATE_H_

#include <string>

#include "base/macros.h"
#include "ui/views/view.h"

namespace views {
class View;
}  // namespace views

namespace ambiesoft {
namespace dicregate {

class SplitterViewDelegate {
 public:
  // OnResize is sent when resizing is detected. |resize_amount| specifies the
  // number of pixels that the user wants to resize by, and can be negative or
  // positive (depending on direction of dragging and flips according to
  // locale directionality: dragging to the left in LTR locales gives negative
  // |resize_amount| but positive amount for RTL). |done_resizing| is true if
  // the user has released the pointer (mouse, stylus, touch, etc.).
  virtual void OnResize(int resize_amount, bool done_resizing) = 0;

 protected:
  virtual ~SplitterViewDelegate() = default;
};

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // AMBIESOFT_SPLITTER_VIEW_DELEGATE_H_
