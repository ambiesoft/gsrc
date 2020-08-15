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

namespace ambiesoft {
namespace gndev {

const char kGndevWidgetName[] = "GndevWidget";

base::LazyInstance<base::TestDiscardableMemoryAllocator>::DestructorAtExit
    g_discardable_memory_allocator = LAZY_INSTANCE_INITIALIZER;

class GndevWindowContents : public views::WidgetDelegateView,
                            public ui::TableModel {
 public:
  GndevWindowContents(base::OnceClosure on_close)
      : on_close_(std::move(on_close)) {
    SetHasWindowSizeControls(true);

    instance_ = this;

    SetBackground(views::CreateThemedSolidBackground(
        this, ui::NativeTheme::kColorId_DialogBackground));

    views::GridLayout* layout =
        SetLayoutManager(std::make_unique<views::GridLayout>());

    // Create Table
    std::vector<ui::TableColumn> columns;
    ui::TableColumn column1;
    column1.id = 0;
    column1.title = ASCIIToUTF16("aaa");
    column1.sortable = false;
    columns.push_back(column1);

    ui::TableColumn column2;
    column2.id = 1;
    column2.title = ASCIIToUTF16("bbb");
    column2.sortable = false;
    columns.push_back(column2);

    auto table = std::make_unique<views::TableView>(this, columns,
                                                    views::ICON_AND_TEXT, true);

    // table->SetGrouper(this);
    // table->set_observer(this);
    // icon1_.allocN32Pixels(16, 16);
    // SkCanvas canvas1(icon1_);
    // canvas1.drawColor(SK_ColorRED);

    // icon2_.allocN32Pixels(16, 16);
    // SkCanvas canvas2(icon2_);
    // canvas2.drawColor(SK_ColorBLUE);

    views::ColumnSet* column_set = layout->AddColumnSet(0);
    column_set->AddColumn(
        views::GridLayout::FILL,        // h-align
        views::GridLayout::FILL,        // v-align
        1,                              // resize percent
        views::GridLayout::ColumnSize::kUsePreferred, // 
        0,                              // fixed width
        0                               // min width
    );
    layout->StartRow(
        1,      // expand (vertical resize)
        0       // column set id
    );
    
    layout->AddView(
        views::TableView::CreateScrollViewWithTable(std::move(table)));

    column_set->AddPaddingColumn(
        0,      // resize percent
        5       // width
    );
    layout->AddPaddingRow(
        0,      // vertical resize
        5       // pixel count
    );


    // status label
    layout->StartRow(
        0,      // no expand (vertical resize)
        0       // column set id
    );
    status_label_ = layout->AddView(std::make_unique<views::Label>());
    layout->AddPaddingRow(0, 5);
  }

  ~GndevWindowContents() override {}

  // TableModel overrides
  int RowCount() override { return 1; }
  base::string16 GetText(int row, int column_id) override {
    return ASCIIToUTF16("ggg");
  }
  void SetObserver(ui::TableModelObserver* observer) override {}


  // Sets the status area (at the bottom of the window) to |status|.
  void SetStatus(const std::string& status) {
    status_label_->SetText(base::UTF8ToUTF16(status));
  }

  static GndevWindowContents* instance() { return instance_; }

 private:
  // WidgetDelegateView:
  base::string16 GetWindowTitle() const override {
    return base::ASCIIToUTF16("Views Examples");
  }
  void WindowClosing() override {
    instance_ = nullptr;
    if (on_close_)
      std::move(on_close_).Run();
  }
  gfx::Size CalculatePreferredSize() const override {
    gfx::Size size(800, 300);
    return size;
  }

  static GndevWindowContents* instance_;
  // View* example_shown_ = nullptr;
  views::Label* status_label_ = nullptr;
  base::OnceClosure on_close_;
  // Combobox* combobox_ = nullptr;
  // Owned by |combobox_|.
  // ComboboxModelExampleList* combobox_model_ = nullptr;

  DISALLOW_COPY_AND_ASSIGN(GndevWindowContents);
};

// static
GndevWindowContents* GndevWindowContents::instance_ = nullptr;

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

GndevExitCode GndevMainProc(bool under_test) {
#if defined(OS_WIN)
  ui::ScopedOleInitializer ole_initializer;
#endif

  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();

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

  base::FilePath views_examples_resources_pak_path;
  CHECK(base::PathService::Get(base::DIR_MODULE,
                               &views_examples_resources_pak_path));
  ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
      views_examples_resources_pak_path.AppendASCII(
          "views_examples_resources.pak"),
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
