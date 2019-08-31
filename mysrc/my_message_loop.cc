// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
// https://www.chromium.org/developers/cpp-in-chromium-101-codelab

#include <stdio.h>

#include "base/command_line.h"
#include "base/at_exit.h"
#include "base/location.h"
#include "base/message_loop/message_loop.h"
#include "base/run_loop.h"
#include "base/strings/string_number_conversions.h"
#include "base/time/time.h"

using namespace base;

int main(int argc, char* argv[]) {
  base::AtExitManager exit_manager;

  CHECK_GE(puts("Hello, world!"), 0);
  LOG(INFO) << "Hello, logging!";

  CHECK(CommandLine::Init(argc, argv));
  CommandLine& command_line = *CommandLine::ForCurrentProcess();
  std::string greeting = command_line.GetSwitchValueASCII("greeting");
  if (greeting.empty()) 
	  greeting = "Hello";
  
  std::string name = command_line.GetSwitchValueASCII("name");
  if (name.empty()) 
	  name = "world";
  CHECK_GT(printf("%s, %s!\n", greeting.c_str(), name.c_str()), 0);
  LOG(INFO) << greeting << ", " << name << "!";
 
  //if (argc <= 1) {
  //  printf("%s: missing operand\n", argv[0]);
  //  return -1;
  //}

  if (command_line.GetSwitchValueASCII("duration").empty())
	  command_line.AppendSwitchASCII("duration", "10");
  DCHECK(!command_line.GetSwitchValueASCII("duration").empty());
  int duration_seconds = 0;
  if (!base::StringToInt(command_line.GetSwitchValueASCII("duration"), &duration_seconds) ||
	  duration_seconds < 0) {
	  printf("%s: invalid time interval `%s'\n", argv[0], argv[1]);
	  return -1;
  }

  base::TimeDelta duration = base::TimeDelta::FromSeconds(duration_seconds);
  base::MessageLoop main_loop;
  base::RunLoop run_loop;
  
  main_loop.task_runner()->PostDelayedTask(FROM_HERE, run_loop.QuitClosure(),
                                           duration);
  
  // main_loop does not have PostDelayedTask
  // main_loop.PostDelayedTask(FROM_HERE, run_loop.QuitClosure(), duration);

  run_loop.Run();

  return 0;
}