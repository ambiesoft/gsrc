// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_window.h"
#include "splitter_view.h"

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
#include "ui/base/models/table_model.h"
#include "ui/base/ui_base_paths.h"
#include "ui/views/background.h"
#include "ui/views/controls/combobox/combobox.h"
// #include "ui/views/controls/combobox/combobox_listener.h"
#include "ui/views/controls/label.h"
#include "ui/views/controls/scroll_view.h"
#include "ui/views/controls/table/table_view.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/grid_layout.h"
#include "ui/views/layout/box_layout.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"

using views::GridLayout;
using views::BoxLayout;
using views::ColumnSet;
using views::Label;
using views::Widget;
using views::TableView;
using ui::TableColumn;

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
  GridLayout* rootLayout = SetLayoutManager(std::make_unique<GridLayout>());

  enum { 
      kGridColumnSetToolbar, kGridColumnSetMain, kGridColumnSetStatus
  };

  // toolbar column
  {
    ColumnSet* column_set_toolbar =
        rootLayout->AddColumnSet(kGridColumnSetToolbar);
    column_set_toolbar->AddColumn(
        GridLayout::FILL,
        GridLayout::FILL,                       // h- and v-align
        1,                                      // resize percent
        GridLayout::ColumnSize::kUsePreferred,  // size
        0,                                      // fix width
        0                                       // minwidth
    );

    // add toolbar
  }

  // main column
  {
    const float kInitResizePercents[] = {0.2f, 0.8f};
    ColumnSet* column_set_main = rootLayout->AddColumnSet(kGridColumnSetMain);
    // Left pane
    column_set_main->AddColumn(
        GridLayout::FILL,
        GridLayout::FILL,                       // h- and v-align
        kInitResizePercents[0],  // resize percent
        GridLayout::ColumnSize::kUsePreferred,  // size
        0,
        //GridLayout::ColumnSize::kFixed,  // size
        //70,  // fix width
        0                                       // minwidth
    );

    // splitter
    // column_set_main->AddPaddingColumn(0.0f, 10);
    column_set_main->AddColumn(GridLayout::FILL,
                               GridLayout::FILL,  // h- and v-align
                               0.0f,              // resize percent
                               GridLayout::ColumnSize::kFixed,  // size
                               10,  // fix width
                               10   // minwidth
    );

    // right pane
    column_set_main->AddColumn(GridLayout::FILL,
                               GridLayout::FILL,  // h- and v-align
                               kInitResizePercents[1],  // resize percent
                               GridLayout::ColumnSize::kUsePreferred,  // size
                               0,  // fix width
                               0   // minwidth
    );

    //auto mainRootView = std::make_unique<View>();
    //BoxLayout* mainBox = mainRootView->SetLayoutManager(
    //    std::make_unique<BoxLayout>(BoxLayout::Orientation::kHorizontal));

    // auto leftRootView = std::make_unique<View>();
    {
      //BoxLayout* leftBoxLayout = leftRootView->SetLayoutManager(
      //    std::make_unique<BoxLayout>(BoxLayout::Orientation::kVertical));

      // Create Table for heading search results
      std::vector<TableColumn> columns;
      {
        TableColumn column1;
        column1.id = kTableColumnWord;
        column1.title = base::ASCIIToUTF16("word");
        column1.sortable = false;
        columns.push_back(column1);
      }
      {
        TableColumn column2;
        column2.id = kTableColumnDictionary;
        column2.title = base::ASCIIToUTF16("dictionary");
        column2.sortable = false;
        columns.push_back(column2);
      }

      auto table = std::make_unique<TableView>(this,  // TableModel
                                               columns, views::ICON_AND_TEXT,
                                               true  // single selection
      );
      table_ = table.get();
      table->set_observer(this);
      table->SetSortOnPaint(false);

      // Create top-left view with scroll capability
      auto vList = TableView::CreateScrollViewWithTable(std::move(table));
      vTopLeft_ = vList.get();
      gfx::Size size(100, 200);
      vTopLeft_->SetPreferredSize(size);
      vTopLeft_->SetSize(size);

      // View* tv = v.get();
      // leftRootView->AddChildView(std::move(v));
      // leftBoxLayout->SetFlexForView(tv, 1);
      // leftRootView->AddView(v);

      // Add TreeView for history
      // TODO
      auto vTree = std::make_unique<View>();

    
      // splitter
      auto vSplitter = std::make_unique<SplitterView>(this);
                      
    
      webViewDicregate->CreateDicregateView();
      webViewDicregate_ = webViewDicregate.get();
      //webViewDicregate_->SetPreferredSize(size);
      //webViewDicregate_->SetSize(size);
      // leftView->AddChildView(std::move(webViewDicregate));
      //mainBox->SetFlexForView(webViewDicregate_,1);


      rootLayout->StartRow(0.7f,  // expand?
                           kGridColumnSetMain);
      rootLayout->AddView(std::move(vList));
      rootLayout->AddView(std::move(vSplitter), 1, 2);

      // 2 rows
      rootLayout->AddView(std::move(webViewDicregate), 1, 2);

      rootLayout->StartRow(0.3f,  // expand?
                           kGridColumnSetMain);
      rootLayout->AddView(std::move(vTree));
    }
  }


  {
    ColumnSet* column_set_status =
        rootLayout->AddColumnSet(kGridColumnSetStatus);
    column_set_status->AddColumn(
        GridLayout::FILL,
        GridLayout::FILL,                       // h- and v-align
        1,                                      // resize percent
        GridLayout::ColumnSize::kUsePreferred,  // size
        0,                                      // fix width
        0                                       // minwidth
    );
    rootLayout->StartRow(0.0f,  // no expand
                     kGridColumnSetStatus);

    status_label_ = rootLayout->AddView(std::make_unique<Label>());
    // rootLayout->AddPaddingRow(0, 5);
  }
}

void DicregateWindowContents::OnResize(int resize_amount,
                                       bool done_resizing) 
{
  VLOG(0) << resize_amount << ":" << done_resizing;
  
  if (!done_resizing)
    return;
  
  // base::AutoReset<bool> auResizing(&resizing_, true);

  //views::View* v = nullptr;
  //
  //if (resize_amount < 0) {
  //  v = webViewDicregate_;
  //  resize_amount = -resize_amount;
  //} else {
  //  v = vTopLeft_;
  //}

  //gfx::Size size = v->size();
  //gfx::Size prefSize = v->GetPreferredSize();
  //size.set_width(size.width() + resize_amount);
  //size.set_height(prefSize.height());
  //v->SetPreferredSize(size);


  // gfx::Size size = vTopLeft_->size();
  //gfx::Size prefSize = vTopLeft_->GetPreferredSize();
  //size.set_width(size.width() + resize_amount);
  //size.set_height(prefSize.height());
  //vTopLeft_->SetPreferredSize(size);

  // gfx::Size size = vTopLeft_->size();
  gfx::Size prefSize = vTopLeft_->GetPreferredSize();
  prefSize.set_width(prefSize.width() + resize_amount);
  prefSize.set_height(prefSize.height());
  vTopLeft_->SetPreferredSize(prefSize);
  // vTopLeft_->SetSize(prefSize);

  // Layout();
}

//void DicregateWindowContents::PreferredSizeChanged() {
//  if (resizing_)
//    return;
//  views::WidgetDelegateView::PreferredSizeChanged();
//}

int DicregateWindowContents::RowCount() {
  return 1;
}
base::string16 DicregateWindowContents::GetText(int row, int column_id) {
  static base::string16 ggg = base::ASCIIToUTF16("ggg");
  static base::string16 hhh = base::ASCIIToUTF16("hhh");
  switch (column_id) {
    case kTableColumnWord:
      return hhh;
    case kTableColumnDictionary:
      return ggg;
  }
  NOTREACHED();
  return base::string16();
}

// TableViewObserver:
void DicregateWindowContents::OnSelectionChanged() {}
void DicregateWindowContents::OnDoubleClick() {}
void DicregateWindowContents::OnMiddleClick() {}
void DicregateWindowContents::OnKeyDown(ui::KeyboardCode virtual_keycode) {}

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
  gfx::Size size(800, 600);
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
