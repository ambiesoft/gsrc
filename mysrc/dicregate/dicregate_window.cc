// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_window.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <utility>

#include "base/command_line.h"
#include "base/macros.h"
#include "base/run_loop.h"
#include "base/stl_util.h"
#include "base/strings/string_split.h"
#include "base/strings/utf_string_conversions.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/combobox_model.h"
#include "ui/base/ui_base_paths.h"
#include "ui/views/background.h"
#include "ui/views/controls/combobox/combobox.h"
#include "ui/views/controls/combobox/combobox_listener.h"
#include "ui/views/controls/label.h"
#include "ui/views/examples/create_examples.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/grid_layout.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

using views::GridLayout;
using views::ColumnSet;
using views::Label;
using views::Widget;

namespace ambiesoft {
namespace dicregate {

const char kExamplesWidgetName[] = "ExamplesWidget";

DicregateWindowContents::DicregateWindowContents(
    base::OnceClosure on_close,
    std::unique_ptr<WebViewDicregate> webViewDicregate)
    : on_close_(std::move(on_close)) {
  SetHasWindowSizeControls(true);

  instance_ = this;

  SetBackground(CreateThemedSolidBackground(
      this, ui::NativeTheme::kColorId_DialogBackground));
  GridLayout* layout = SetLayoutManager(std::make_unique<GridLayout>());

  constexpr int kColumnSetId = 0;
  ColumnSet* column_set = layout->AddColumnSet(kColumnSetId);
  //column_set->AddPaddingColumn(0,  // resize percent
  //                             5   // width
  //);
  column_set->AddColumn(GridLayout::FILL, GridLayout::FILL,  // h- and v-align
                        1,                                   // resize percent
                        GridLayout::ColumnSize::kUsePreferred,  // size
                        0,                                      // fix width
                        0                                       // minwidth
  );
  column_set->AddPaddingColumn(0, 5);

  layout->AddPaddingRow(0, 5);
  layout->StartRow(1, 0);
  // combobox_ = layout->AddView(std::move(combobox));

  webViewDicregate->CreateDicregateView();
  webViewDicregate_ = webViewDicregate.get();
  layout->AddView(std::move(webViewDicregate));

  // auto item_count = combobox_model_->GetItemCount();
  // if (item_count > 0) {
  //  combobox_->SetVisible(item_count > 1);
  //  layout->StartRow(1, 0);
  //  auto example_shown = std::make_unique<View>();
  //  example_shown->SetLayoutManager(std::make_unique<FillLayout>());
  //  example_shown->AddChildView(combobox_model_->GetItemViewAt(0));
  //  example_shown_ = layout->AddView(std::move(example_shown));
  //}

  layout->StartRow(0 /* no expand */, 0);
  status_label_ = layout->AddView(std::make_unique<Label>());
  layout->AddPaddingRow(0, 5);
}

 void DicregateWindowContents::SetStatus(const std::string& status) {
  status_label_->SetText(base::UTF8ToUTF16(status));
}

base::string16 DicregateWindowContents::GetWindowTitle() const {
  return base::ASCIIToUTF16("Views Examples");
}
void DicregateWindowContents::WindowClosing() {
  instance_ = nullptr;
  if (on_close_)
    std::move(on_close_).Run();
}
gfx::Size DicregateWindowContents::CalculatePreferredSize() const {
  gfx::Size size(800, 300);
  // for (int i = 0; i < combobox_model_->GetItemCount(); i++) {
  //  size.set_height(
  //      std::max(size.height(),
  //               combobox_model_->GetItemViewAt(i)->GetHeightForWidth(800)));
  //}
  return size;
}

// static
DicregateWindowContents* DicregateWindowContents::instance_ = nullptr;

void ShowDicregateWindow(base::OnceClosure on_close,
                        std::unique_ptr<WebViewDicregate> webViewDicregate,
                        gfx::NativeWindow window_context) {
  if (DicregateWindowContents::instance()) {
    DicregateWindowContents::instance()->GetWidget()->Activate();
  } else {
    Widget* widget = new Widget;
    Widget::InitParams params;
    params.delegate =
        new DicregateWindowContents(std::move(on_close), std::move(webViewDicregate));
    params.context = window_context;
    params.name = kExamplesWidgetName;
    widget->Init(std::move(params));
    widget->Show();
  }
}

void LogStatus(const std::string& string) {
  if (DicregateWindowContents::instance())
    DicregateWindowContents::instance()->SetStatus(string);
}

}  // namespace dicregate
}  // namespace ambiesoft
