# GPUプロセスの起動順序

1. content.dll!content::BrowserMainLoop::CreateStartupTasks()でBrowserMainLoop::BrowserThreadsStartedを登録。
2. BrowserMainLoop::BrowserThreadsStarted()がキューから呼ばれる（まだメインスレッド）。この時点でIOスレッドはすでに動いている。ここではまずMOJOを初期化、MOJOの初期化にはIOスレッドが必要なので、まずこれをやっている。
3. BrowserGpuChannelHostFactoryを作成し、IOスレッドにEstablishRequest::EstablishOnIOを投げる。
4. IOスレッドでEstablishRequest::EstablishOnIO()が実行される。
5. IOスレッドでGpuProcessHostが作成される。
6. GpuProcessHostはprocess_をもつ。これを作成する（BrowserChildProcessHostImpl(PROCESS_TYPE_GPU))
7. プロセスの管理やIPCはChildProcessHostImplが行う。このクラスはmojoクラスをもつ。
8. GetProcessLauncherTaskにLaunchOnLauncherThreadを投げる。ここでプロセスを起動する。
9. 


複雑性
所得の配分のいびつさ
マネーストックが動いてない
利息が発生していて銀行に集中している

高齢者と若者の時間

