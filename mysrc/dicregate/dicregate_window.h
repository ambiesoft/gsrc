// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_DICREGATE_WINDOW_H_
#define AMBIESOFT_DICREGATE_WINDOW_H_

#include <memory>
#include <string>
#include <vector>

#include "webview_dicregate.h"
#include "base/callback_forward.h"
#include "base/strings/stringprintf.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/controls/label.h"
#include "ui/base/models/table_model.h"
#include "ui/views/controls/table/table_view_observer.h"

namespace views {
class TableView;
}  // namespace views

namespace ambiesoft {
namespace dicregate {

extern const char kExamplesWidgetName[];

// Shows a window with the views examples in it. |extra_examples| contains any
// additional examples to add. |window_context| is used to determine where the
// window should be created (see |Widget::InitParams::context| for details).
void ShowDicregateWindow(
    base::OnceClosure on_close,
    std::unique_ptr<WebViewDicregate> webViewDicregate,
    gfx::NativeWindow window_context = nullptr);

// Prints |string| in the status area, at the bottom of the window.
void LogStatus(const std::string& string);

// Same as LogStatus(), but with a format string.
template <typename... Args>
void PrintStatus(const char* format, Args... args) {
  LogStatus(base::StringPrintf(format, args...));
}


class DicregateWindowContents : public views::WidgetDelegateView,
                                public ui::TableModel,
                                public views::TableViewObserver {
  enum {
    kTableColumnWord,
    kTableColumnDictionary,
  };
 public:
  DicregateWindowContents(base::OnceClosure on_close,
                          std::unique_ptr<WebViewDicregate> webViewDicregate);
  ~DicregateWindowContents() override = default;

  // TableModel overrides
  int RowCount() override;
  base::string16 GetText(
      int row, int column_id) override;
  void SetObserver(ui::TableModelObserver * observer) override {}

  // TableViewObserver:
  void OnSelectionChanged() override;
  void OnDoubleClick() override;
  void OnMiddleClick() override;
  void OnKeyDown(ui::KeyboardCode virtual_keycode) override;

  // Sets the status area (at the bottom of the window) to |status|.
  void SetStatus(const std::string& status);

  static DicregateWindowContents* instance() { return instance_; }

 private:
  // WidgetDelegateView:
  base::string16 GetWindowTitle() const override;
  void WindowClosing() override;
  gfx::Size CalculatePreferredSize() const override;

  static DicregateWindowContents* instance_;

  base::OnceClosure on_close_;

  views::TableView* table_ = nullptr;
  WebViewDicregate* webViewDicregate_ = nullptr;
  views::Label* status_label_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(DicregateWindowContents);
};

}  // namespace examples
}  // namespace views

#endif  // AMBIESOFT_DICREGATE_WINDOW_H_
