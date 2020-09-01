// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "dicregate_content_main_delegate.h"
#include "dicregate_content_browser_client.h"
#include "dicregate_content_browser_client.h"
#include "dicregate_content_client_main_parts.h"

#include <string>

#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/path_service.h"
#include "build/build_config.h"
#include "content/public/common/content_switches.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/base/ui_base_paths.h"


#if defined(OS_WIN)
#include "base/logging_win.h"
#endif

namespace ambiesoft {
namespace dicregate {

    namespace {

#if defined(OS_WIN)
// {83FAC8EE-7A0E-4dbb-A3F6-6F500D7CAB1A}
const GUID kViewsContentClientProviderName = {
    0x83fac8ee,
    0x7a0e,
    0x4dbb,
    {0xa3, 0xf6, 0x6f, 0x50, 0xd, 0x7c, 0xab, 0x1a}};
#endif

}  // namespace

DicregateContentMainDelegate::DicregateContentMainDelegate(
    DicregateContentClient* dicregate_content_client)
    : dicregate_content_client_(dicregate_content_client) {}

DicregateContentMainDelegate::~DicregateContentMainDelegate() {}

bool DicregateContentMainDelegate::BasicStartupComplete(int* exit_code) {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  std::string process_type =
      command_line.GetSwitchValueASCII(switches::kProcessType);

  logging::LoggingSettings settings;
  settings.logging_dest =
      logging::LOG_TO_SYSTEM_DEBUG_LOG | logging::LOG_TO_STDERR;
  bool success = logging::InitLogging(settings);
  CHECK(success);
#if defined(OS_WIN)
  logging::LogEventProvider::Initialize(kViewsContentClientProviderName);
#endif

  return false;
}

void DicregateContentMainDelegate::PreSandboxStartup() {
  base::FilePath ui_test_pak_path;
  CHECK(base::PathService::Get(ui::UI_TEST_PAK, &ui_test_pak_path));
  ui::ResourceBundle::InitSharedInstanceWithPakPath(ui_test_pak_path);

  // Load content resources to provide, e.g., sandbox configuration data on Mac.
  base::FilePath content_resources_pak_path;
  base::PathService::Get(base::DIR_MODULE, &content_resources_pak_path);
  ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
      content_resources_pak_path.AppendASCII("content_resources.pak"),
      ui::SCALE_FACTOR_100P);

  if (ui::ResourceBundle::IsScaleFactorSupported(ui::SCALE_FACTOR_200P)) {
    base::FilePath ui_test_resources_200 = ui_test_pak_path.DirName().Append(
        FILE_PATH_LITERAL("ui_test_200_percent.pak"));
    ui::ResourceBundle::GetSharedInstance().AddDataPackFromPath(
        ui_test_resources_200, ui::SCALE_FACTOR_200P);
  }

  dicregate_content_client_->OnResourcesLoaded();
}

void DicregateContentMainDelegate::PreCreateMainMessageLoop() {
  content::ContentMainDelegate::PreCreateMainMessageLoop();
  DicregateContentClientMainParts::PreCreateMainMessageLoop();
}

content::ContentClient* DicregateContentMainDelegate::CreateContentClient() {
  return &content_client_;
}

content::ContentBrowserClient*
DicregateContentMainDelegate::CreateContentBrowserClient() {
  browser_client_ =
      std::make_unique<DicregateContentBrowserClient>(dicregate_content_client_);
  return browser_client_.get();
}

}  // namespace dicregate
}  // namespace ambiesoft
