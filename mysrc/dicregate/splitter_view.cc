// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "splitter_view.h"
#include "splitter_view_delegate.h"

#include "ui/accessibility/ax_enums.mojom.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/base/cursor/cursor.h"
#include "ui/views/controls/resize_area_delegate.h"
#include "ui/views/metadata/metadata_impl_macros.h"
#include "ui/views/native_cursor.h"

namespace ambiesoft {
namespace dicregate {


SplitterView::SplitterView(SplitterViewDelegate* delegate)
    : delegate_(delegate), initial_position_(0) {}

SplitterView::~SplitterView() = default;

gfx::NativeCursor SplitterView::GetCursor(const ui::MouseEvent& event) {
  return GetEnabled() ? views::GetNativeEastWestResizeCursor() : gfx::kNullCursor;
}

void SplitterView::OnGestureEvent(ui::GestureEvent* event) {
  if (event->type() == ui::ET_GESTURE_TAP_DOWN) {
    SetInitialPosition(event->x());
    event->SetHandled();
  } else if (event->type() == ui::ET_GESTURE_SCROLL_BEGIN ||
             event->type() == ui::ET_GESTURE_SCROLL_UPDATE) {
    ReportResizeAmount(event->x(), false);
    event->SetHandled();
  } else if (event->type() == ui::ET_GESTURE_END) {
    ReportResizeAmount(event->x(), true);
    event->SetHandled();
  }
}

bool SplitterView::OnMousePressed(const ui::MouseEvent& event) {
  if (!event.IsOnlyLeftMouseButton())
    return false;

  SetInitialPosition(event.x());
  return true;
}

bool SplitterView::OnMouseDragged(const ui::MouseEvent& event) {
  if (!event.IsLeftMouseButton())
    return false;

  ReportResizeAmount(event.x(), false);
  return true;
}

void SplitterView::OnMouseReleased(const ui::MouseEvent& event) {
  ReportResizeAmount(event.x(), true);
}

void SplitterView::OnMouseCaptureLost() {
  gfx::Point point(initial_position_, 0);
  View::ConvertPointFromScreen(this, &point);
  ReportResizeAmount(point.x(), true);
}

void SplitterView::GetAccessibleNodeData(ui::AXNodeData* node_data) {
  node_data->role = ax::mojom::Role::kSplitter;
}

void SplitterView::ReportResizeAmount(int resize_amount, bool last_update) {
  gfx::Point point(resize_amount, 0);
  View::ConvertPointToScreen(this, &point);
  resize_amount = point.x() - initial_position_;
  delegate_->OnResize(base::i18n::IsRTL() ? -resize_amount : resize_amount,
                      last_update);
}

void SplitterView::SetInitialPosition(int event_x) {
  gfx::Point point(event_x, 0);
  View::ConvertPointToScreen(this, &point);
  initial_position_ = point.x();
}


}  // namespace dicregate
}  // namespace ambiesoft
