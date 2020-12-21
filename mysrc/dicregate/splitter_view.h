// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_SPLITTER_VIEW_H_
#define AMBIESOFT_SPLITTER_VIEW_H_

#include <string>

#include "base/macros.h"
#include "ui/views/view.h"

namespace views {
class View;
}  // namespace views

namespace ambiesoft {
namespace dicregate {

class SplitterViewDelegate;

class SplitterView : public views::View {
 public:
  explicit SplitterView(SplitterViewDelegate* delegate);
  ~SplitterView() override;

  // views::View:
  gfx::NativeCursor GetCursor(const ui::MouseEvent& event) override;
  void OnGestureEvent(ui::GestureEvent* event) override;
  bool OnMousePressed(const ui::MouseEvent& event) override;
  bool OnMouseDragged(const ui::MouseEvent& event) override;
  void OnMouseReleased(const ui::MouseEvent& event) override;
  void OnMouseCaptureLost() override;
  void GetAccessibleNodeData(ui::AXNodeData* node_data) override;

 private:
  // Report the amount the user resized by to the delegate, accounting for
  // directionality.
  void ReportResizeAmount(int resize_amount, bool last_update);

  // Converts |event_x| to screen coordinates and sets |initial_position_| to
  // this value.
  void SetInitialPosition(int event_x);

  // The delegate to notify when we have updates.
  SplitterViewDelegate* delegate_;

  // The event's x-position at the start of the resize operation. The resize
  // area will move while being dragged, so |initial_position_| is represented
  // in screen coordinates so that we don't lose our bearings.
  int initial_position_;

  DISALLOW_COPY_AND_ASSIGN(SplitterView);
};

}  // namespace dicregate
}  // namespace ambiesoft

#endif  // AMBIESOFT_SPLITTER_VIEW_H_
