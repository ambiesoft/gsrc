// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content.h"
#include "dicregate_content_client.h"
#include "dicregate_content_main_delegate.h"

#include "base/bind.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "build/build_config.h"
#include "content/public/browser/browser_context.h"
#include "content/public/app/content_main.h"
#include "ui/base/resource/resource_bundle.h"

#if defined(OS_MACOSX)
#include "sandbox/mac/seatbelt_exec.h"
#endif

#if defined(OS_WIN)
#include "content/public/app/sandbox_helper_win.h"
#include "sandbox/win/src/sandbox_types.h"
#endif

using ambiesoft::dicregate::DicregateContentClient;

namespace {

void OnResourcesLoaded() {
  base::FilePath views_examples_resources_pak_path;
  CHECK(base::PathService::Get(base::DIR_MODULE,
                               &views_examples_resources_pak_path));
  ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
      views_examples_resources_pak_path.AppendASCII(
          "views_examples_resources.pak"),
      ui::SCALE_FACTOR_100P);
}

void ShowDicregate(DicregateContentClient* dicregate_content_client,
                   content::BrowserContext* browser_context,
                   gfx::NativeWindow window_context) {
  ambiesoft::dicregate::ShowDicregateContent(
      std::move(dicregate_content_client->quit_closure()), browser_context,
      window_context);

  // These lines serve no purpose other than to introduce an explicit content
  // dependency. If the main executable doesn't have this dependency, the linker
  // has more flexibility to reorder library dependencies in a shared component
  // build. On linux, this can cause libc to appear before libcontent in the
  // dlsym search path, which breaks (usually valid) assumptions made in
  // sandbox::InitLibcUrandomOverrides(). See http://crbug.com/374712.
  if (!browser_context) {
    content::BrowserContext::SaveSessionState(nullptr);
    NOTREACHED();
  }
}

}  // namespace

#if defined(OS_WIN)
int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE, wchar_t*, int) {
  sandbox::SandboxInterfaceInfo sandbox_info = {nullptr};
  content::InitializeSandboxInfo(&sandbox_info);
  DicregateContentClient dicregate_content_client(instance, &sandbox_info);
#else
int main(int argc, const char** argv) {
  base::CommandLine::Init(argc, argv);
  DicregateContentClient dicregate_content_client(argc, argv);
#endif


#if defined(OS_MACOSX)
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  // ViewsContentClient expects a const char** argv and
  // CreateFromArgumentsResult expects a regular char** argv. Given this is a
  // test program, a refactor from either end didn't seem worth it. As a result,
  // use a const_cast instead.
  sandbox::SeatbeltExecServer::CreateFromArgumentsResult seatbelt =
      sandbox::SeatbeltExecServer::CreateFromArguments(
          command_line->GetProgram().value().c_str(), argc,
          const_cast<char**>(argv));
  if (seatbelt.sandbox_required)
    CHECK(seatbelt.server->InitializeSandbox());
#endif

  dicregate_content_client.set_on_resources_loaded_callback(
      base::BindOnce(&OnResourcesLoaded));
  dicregate_content_client.set_on_pre_main_message_loop_run_callback(
      base::BindOnce(&ShowDicregate,
                     base::Unretained(&dicregate_content_client)));

  ambiesoft::dicregate::DicregateContentMainDelegate delegate(&dicregate_content_client);
  content::ContentMainParams params(&delegate);

#if defined(OS_WIN)
  params.instance = dicregate_content_client.instance();
  params.sandbox_info = dicregate_content_client.sandbox_info();
#else
  params.argc = argc_;
  params.argv = argv_;
#endif

  return content::ContentMain(params);
}
