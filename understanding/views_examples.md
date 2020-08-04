# 全体の流れ
```
ui::ScopedOleInitializer ole_initializer
mojo::core::Init();
gl::init::InitializeGLOneOff();
base::test::TaskEnvironment 

// タスクキューなどの準備
task_environment(base::test::TaskEnvironment::MainThreadType::UI);

// Set up the compositor ContextFactory
// FrameSinkなどのセットアップ
auto context_factories = std::make_unique<ui::TestContextFactories>(under_test);

base::i18n::InitializeICU();

ui::RegisterPathProvider();

Initialize ui::ResourceBundle

base::PowerMonitor::Initialize(std::make_unique<base::PowerMonitorDeviceSource>());

gfx::InitializeFonts();

std::unique_ptr<aura::Env> env = aura::Env::CreateInstance();
aura::Env::GetInstance()->set_context_factory(context_factories->GetContextFactory());

{
  // Desktop native widgetを使うようになり、WidgetがHWNDのWindowをつくるようになる
  views::DesktopTestViewsDelegate views_delegate;

  std::unique_ptr<display::Screen> desktop_screen = base::WrapUnique(views::CreateDesktopScreen());

  base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);

　// このアプリのビューをつくる
　views::examples::ShowExamplesWindow(run_loop.QuitClosure());

  // アプリ起動中はこのキューでタスクが回る
  run_loop.Run();

  ui::ResourceBundle::CleanupSharedInstance();
}

ui::ShutdownInputMethod();
env.reset();
```

# このアプリのトップウインドウ
## 上部のコンボボックス
