// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_GNDEV_MAIN_PROC_H_
#define AMBIESOFT_GNDEV_MAIN_PROC_H_

#include "gn_exit_code.h"

#include "ui/views/widget/widget_delegate.h"
#include "ui/base/models/table_model.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/table/table_view.h"
#include "ui/views/controls/table/table_view_observer.h"

namespace ambiesoft {
namespace gndev {

GndevExitCode GndevMainProc(bool under_test = false);

class GndevWindowContents : public views::WidgetDelegateView,
                            public ui::TableModel,
                            public views::TableViewObserver {
 public:
  GndevWindowContents(base::OnceClosure on_close);
  ~GndevWindowContents() override {}

  enum { 
      kColumnFirst,
      kColumnSecond,
  };

  template <typename... Args>
  void PrintStatus(const char* format, Args... args) {
    SetStatus(base::StringPrintf(format, args...));
  }

  // TableModel overrides
  int RowCount() override;
  base::string16 GetText(int row, int column_id) override;
  void SetObserver(ui::TableModelObserver* observer) override {}

    // TableViewObserver:
  void OnSelectionChanged() override;
  void OnDoubleClick() override;
  void OnMiddleClick() override;
  void OnKeyDown(ui::KeyboardCode virtual_keycode) override;


  // Sets the status area (at the bottom of the window) to |status|.
  void SetStatus(const std::string& status);

  static GndevWindowContents* instance() { return instance_; }

 private:
  // WidgetDelegateView:
  base::string16 GetWindowTitle() const override;
  void WindowClosing() override;
  gfx::Size CalculatePreferredSize() const override;
  void OnWidgetInitialized() override;

 public:
  std::string mytask();
  void mytask2(std::string output);

 private:
  static GndevWindowContents* instance_;
  // View* example_shown_ = nullptr;
  views::TableView* table_ = nullptr;
  views::Label* status_label_ = nullptr;
  base::OnceClosure on_close_;
  // Combobox* combobox_ = nullptr;
  // Owned by |combobox_|.
  // ComboboxModelExampleList* combobox_model_ = nullptr;
  std::vector<base::string16> gnls_;

  DISALLOW_COPY_AND_ASSIGN(GndevWindowContents);
};

}  // namespace gndev
}  // namespace ambiesoft

#endif  // AMBIESOFT_GNDEV_MAIN_PROC_H_
