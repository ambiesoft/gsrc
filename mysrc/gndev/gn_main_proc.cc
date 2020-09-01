// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gn_main_proc.h"

#include <memory>
#include <vector>

#include "base/base_switches.h"
#include "base/bind.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/files/file_path.h"
#include "base/i18n/icu_util.h"
#include "base/lazy_instance.h"
#include "base/memory/ptr_util.h"
#include "base/path_service.h"
#include "base/strings/string_util.h"
#include "base/strings/utf_string_conversions.h"
#include "base/power_monitor/power_monitor.h"
#include "base/power_monitor/power_monitor_device_source.h"
#include "base/run_loop.h"
#include "base/test/scoped_run_loop_timeout.h"
#include "base/test/task_environment.h"
#include "base/test/test_discardable_memory_allocator.h"
#include "base/test/test_timeouts.h"
#include "build/build_config.h"
#include "components/viz/host/host_frame_sink_manager.h"
#include "components/viz/service/display_embedder/server_shared_bitmap_manager.h"
#include "components/viz/service/frame_sinks/frame_sink_manager_impl.h"
#include "mojo/core/embedder/embedder.h"
#include "ui/base/ime/init/input_method_initializer.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"
#include "ui/compositor/compositor_switches.h"
#include "ui/compositor/test/in_process_context_factory.h"
#include "ui/compositor/test/test_context_factories.h"
#include "ui/display/screen.h"
#include "ui/gfx/font_util.h"
#include "ui/gfx/image/image.h"
#include "ui/gl/gl_switches.h"
#include "ui/gl/init/gl_factory.h"
#include "ui/views/buildflags.h"
//#include "ui/views/examples/example_base.h"
//#include "ui/views/examples/examples_window.h"
#include "ui/views/test/desktop_test_views_delegate.h"
#include "ui/views/widget/any_widget_observer.h"
#include "ui/views/widget/widget.h"
#include "ui/views/widget/widget_delegate.h"
#include "ui/views/controls/label.h"
#include "ui/views/layout/fill_layout.h"
#include "ui/views/layout/grid_layout.h"
#include "ui/views/background.h"
#include "ui/views/controls/table/table_view.h"
#include "ui/views/controls/scroll_view.h"
#include "ui/views/controls/textfield/textfield.h"
#include "mysrc/gndev/grit/gndev_resources.h"
#include "ui/base/l10n/l10n_util.h"
#include "base/process/launch.h"
#include "base/files/file_util.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/base/cursor/cursor.h"
#include "ui/views/native_cursor.h"

#if defined(USE_AURA)
#include "ui/aura/env.h"
#include "ui/wm/core/wm_state.h"
#endif

#if BUILDFLAG(ENABLE_DESKTOP_AURA)
#include "ui/views/widget/desktop_aura/desktop_screen.h"
#endif

#if defined(OS_WIN)
#include "ui/base/win/scoped_ole_initializer.h"
#include "ui/views/examples/examples_skia_gold_pixel_diff.h"
#endif

#if defined(USE_OZONE)
#include "ui/base/ui_base_features.h"
#include "ui/ozone/public/ozone_platform.h"
#endif

using base::ASCIIToUTF16;
using views::View;
using views::GridLayout;
using views::TableView;
using views::ColumnSet;
using ui::TableColumn;

namespace ambiesoft {
namespace gndev {

const char kGndevWidgetName[] = "GndevWidget";

base::LazyInstance<base::TestDiscardableMemoryAllocator>::DestructorAtExit
    g_discardable_memory_allocator = LAZY_INSTANCE_INITIALIZER;

base::FilePath gGnRoot;

// static
GndevWindowContents* GndevWindowContents::instance_ = nullptr;

class GnTestView : public View {
  gfx::NativeCursor GetCursor(const ui::MouseEvent& event) override {
    //bool platform_arrow = PlatformStyle::kTextfieldUsesDragCursorWhenDraggable;
    //bool in_selection = GetRenderText()->IsPointInSelection(event.location());
    //bool drag_event = event.type() == ui::ET_MOUSE_DRAGGED;
    //bool text_cursor =
    //    !initiating_drag_ && (drag_event || !in_selection || !platform_arrow);
    //return text_cursor ? GetNativeIBeamCursor() : gfx::kNullCursor;
    return views::GetNativeIBeamCursor();
  }
};

GndevWindowContents::GndevWindowContents(base::OnceClosure on_close)
    : on_close_(std::move(on_close)) {
  SetHasWindowSizeControls(true);

  // std::string sss = l10n_util::GetStringUTF8(IDS_TEST);

  instance_ = this;

  SetBackground(views::CreateThemedSolidBackground(
      this, ui::NativeTheme::kColorId_DialogBackground));

  GridLayout* layout =
      SetLayoutManager(std::make_unique<GridLayout>());


  // icon1_.allocN32Pixels(16, 16);
  // SkCanvas canvas1(icon1_);
  // canvas1.drawColor(SK_ColorRED);

  // icon2_.allocN32Pixels(16, 16);
  // SkCanvas canvas2(icon2_);
  // canvas2.drawColor(SK_ColorBLUE);

  constexpr int kColumnIdFirst = 0;
  ColumnSet* column_set = layout->AddColumnSet(kColumnIdFirst);
  column_set->AddColumn(GridLayout::FILL,  // h-align
                        GridLayout::FILL,  // v-align
                        .7,                        // resize percent
                        GridLayout::ColumnSize::kUsePreferred,  //
                        0,  // fixed width
                        0   // min width
  );
  //column_set->AddPaddingColumn(0,  // resize percent
  //                             5   // width
  //);
  column_set->AddColumn(GridLayout::FILL,     // h-align
                        GridLayout::FILL,  // v-align
                        .3,                // resize percent
                        GridLayout::ColumnSize::kUsePreferred,  //
                        0,                                      // fixed width
                        0                                       // min width
  );


  // Create Table
  {
    std::vector<TableColumn> columns;
    {
      TableColumn column1;
      column1.id = kColumnFirst;
      column1.title = ASCIIToUTF16("aaa");
      column1.sortable = false;
      columns.push_back(column1);
    }
    {
      TableColumn column2;
      column2.id = kColumnSecond;
      column2.title = ASCIIToUTF16("bbb");
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

    // table->SetGrouper(this);
    // table->set_observer(this);

    layout->StartRow(1,              // expand (vertical resize)
                     kColumnIdFirst  // column set id
    );
    layout->AddView(TableView::CreateScrollViewWithTable(std::move(table)),2);
  }



  //layout->AddPaddingRow(0,  // vertical resize
  //                      5   // pixel count
  //);


  // test add treeview
  layout->StartRow(0,              // expand (vertical resize)
                   kColumnIdFirst  // column set id
  );
  layout->AddView(std::make_unique<GnTestView>());
  //layout->AddPaddingRow(0,  // vertical resize
  //                      5   // pixel count
  //);



  // status label
  layout->StartRow(0,  // no expand (vertical resize)
                   kColumnIdFirst  // column set id
  );
  status_label_ = layout->AddView(std::make_unique<views::Label>());
  //layout->AddPaddingRow(0, 5);


  //constexpr int kColumnIdSecond = 1;
  //ColumnSet* column_set2 = layout->AddColumnSet(kColumnIdSecond);
  ////////////////////
  layout->StartRow(0,              // no expand (vertical resize)
                   kColumnIdFirst  // column set id
  );
  {
    views::Textfield* text =
        layout->AddView(std::make_unique<views::Textfield>());
    text->SetText(L"aaa");
    //layout->AddPaddingRow(0, 5);
  }
  //{
  //  views::Textfield* text =
  //      layout->AddView(std::make_unique<views::Textfield>());
  //  text->SetText(L"vvvvvvvvvvvvvvvv");
  //}
}

base::string16 GndevWindowContents::GetWindowTitle() const {
  return base::ASCIIToUTF16("Views Examples");
}
void GndevWindowContents::WindowClosing() {
  instance_ = nullptr;
  if (on_close_)
    std::move(on_close_).Run();
}
gfx::Size GndevWindowContents::CalculatePreferredSize() const {
  gfx::Size size(800, 300);
  return size;
}
void GndevWindowContents::OnWidgetInitialized() {
  base::ThreadPool::PostTaskAndReplyWithResult(
      FROM_HERE, {base::MayBlock()},
      base::BindOnce(&GndevWindowContents::mytask, base::Unretained(this)),
      base::BindOnce(&GndevWindowContents::mytask2, base::Unretained(this)));
}
std::string GndevWindowContents::mytask() {
  if (true)
    return "aaa\nbbb\nccc";

  //base::CommandLine cmdLine =
  //    base::CommandLine::FromString(ASCIIToUTF16("gn.bat"));
  //cmdLine.AppendArg("ls");

  //base::FilePath gnOut(gGnRoot);
  //gnOut = gnOut.AppendASCII("out/debug");
  //cmdLine.AppendArgPath(gnOut);

  //std::string output;
  //int exit_code = -1;
  //if (!base::GetAppOutputWithExitCode(cmdLine, &output, &exit_code)) {
  //  // Failed to start process
  //}
  //if (exit_code != 0) {
  //  // Command failed
  //}
  //return output;
}

void GndevWindowContents::mytask2(std::string output) {
  gnls_.clear();

  std::istringstream f(output);
  std::string line;
  while (std::getline(f, line)) {
    gnls_.push_back(base::UTF8ToUTF16(line));
  }
  table_->OnItemsAdded(0, base::checked_cast<int>(gnls_.size()));
}

int GndevWindowContents::RowCount() {
  return base::checked_cast<int>(gnls_.size());
}
base::string16 GndevWindowContents::GetText(int row, int column_id) {
  static base::string16 ggg = ASCIIToUTF16("ggg");
  switch (column_id) {
    case kColumnFirst:
      return gnls_[row];
    case kColumnSecond:
      return ggg;
  }
  return base::string16();
}

void GndevWindowContents::OnSelectionChanged() {
  PrintStatus("Selected: %s",
              base::UTF16ToASCII(GetText(table_->selection_model().active(), 0))
                  .c_str());
}
void GndevWindowContents::OnDoubleClick() {
  PrintStatus("Double Click: %s",
              base::UTF16ToASCII(GetText(table_->selection_model().active(), 0))
                  .c_str());
}
void GndevWindowContents::OnMiddleClick() {}
void GndevWindowContents::OnKeyDown(ui::KeyboardCode virtual_keycode) {}



void GndevWindowContents::SetStatus(const std::string& status) {
  status_label_->SetText(base::UTF8ToUTF16(status));
}

void ShowGndevWindow(base::OnceClosure on_close) {
  if (GndevWindowContents::instance()) {
    GndevWindowContents::instance()->GetWidget()->Activate();
  } else {
    views::Widget* widget = new views::Widget;
    views::Widget::InitParams params;
    params.delegate = new GndevWindowContents(std::move(on_close));
    // params.context = window_context;
    params.name = kGndevWidgetName;
    widget->Init(std::move(params));
    widget->Show();
  }
}

void SetGnRootPath(const base::FilePath& startPath) {
  base::FilePath result;
  base::FilePath path(startPath);
  base::FilePath lastCheckPath;
  const int kSafebound = 4096;
  for (int up = 0; up < kSafebound; ++up) {
    if (up != 0)
      path = path.AppendASCII("..");
    path = base::MakeAbsoluteFilePath(path);
    if (path == lastCheckPath)
      break;
    lastCheckPath = path;
    base::FilePath gnpath = path.AppendASCII(".gn");
    if (base::PathExists(gnpath))
      gGnRoot = path.NormalizePathSeparatorsTo('/');
  }
}
    
GndevExitCode GndevMainProc(bool under_test) {
#if defined(OS_WIN)
  ui::ScopedOleInitializer ole_initializer;
#endif

  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();

  // Find gn root path
  SetGnRootPath(base::FilePath(base::FilePath::kCurrentDirectory));

  // Disabling Direct Composition works around the limitation that
  // InProcessContextFactory doesn't work with Direct Composition, causing the
  // window to not render. See http://crbug.com/936249.
  command_line->AppendSwitch(switches::kDisableDirectComposition);

  base::FeatureList::InitializeInstance(
      command_line->GetSwitchValueASCII(switches::kEnableFeatures),
      command_line->GetSwitchValueASCII(switches::kDisableFeatures));

  if (under_test)
    command_line->AppendSwitch(switches::kEnablePixelOutputInTests);

  mojo::core::Init();

#if defined(USE_OZONE)
  if (features::IsUsingOzonePlatform()) {
    ui::OzonePlatform::InitParams params;
    params.single_process = true;
    ui::OzonePlatform::InitializeForGPU(params);
  }
#endif

  gl::init::InitializeGLOneOff();

  // Viz depends on the task environment to correctly tear down.
  base::test::TaskEnvironment task_environment(
      base::test::TaskEnvironment::MainThreadType::UI);

  // The ContextFactory must exist before any Compositors are created.
  auto context_factories =
      std::make_unique<ui::TestContextFactories>(under_test);
  context_factories->SetUseTestSurface(false);

  base::i18n::InitializeICU();

  ui::RegisterPathProvider();

  base::FilePath ui_test_pak_path;
  CHECK(base::PathService::Get(ui::UI_TEST_PAK, &ui_test_pak_path));
  ui::ResourceBundle::InitSharedInstanceWithPakPath(ui_test_pak_path);

  base::FilePath gndev_resources_pak_path;
  CHECK(base::PathService::Get(base::DIR_MODULE,
                               &gndev_resources_pak_path));
  ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
      gndev_resources_pak_path.AppendASCII(
          "gndev_resources.pak"),
      ui::SCALE_FACTOR_100P);

  base::DiscardableMemoryAllocator::SetInstance(
      g_discardable_memory_allocator.Pointer());

  base::PowerMonitor::Initialize(
      std::make_unique<base::PowerMonitorDeviceSource>());

  gfx::InitializeFonts();

#if defined(USE_AURA)
  std::unique_ptr<aura::Env> env = aura::Env::CreateInstance();
  aura::Env::GetInstance()->set_context_factory(
      context_factories->GetContextFactory());
#endif
  ui::InitializeInputMethodForTesting();

  GndevExitCode compare_result = GndevExitCode::kSucceeded;

  {
    views::DesktopTestViewsDelegate views_delegate;
#if defined(USE_AURA)
    wm::WMState wm_state;
#endif
#if BUILDFLAG(ENABLE_DESKTOP_AURA)
    std::unique_ptr<display::Screen> desktop_screen =
        base::WrapUnique(views::CreateDesktopScreen());
#endif

    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);

    base::test::ScopedDisableRunLoopTimeout disable_timeout;

    ShowGndevWindow(run_loop.QuitClosure());

    run_loop.Run();

    ui::ResourceBundle::CleanupSharedInstance();
  }

  ui::ShutdownInputMethod();

#if defined(USE_AURA)
  env.reset();
#endif

  return compare_result;
}

}  // namespace examples
}  // namespace views
