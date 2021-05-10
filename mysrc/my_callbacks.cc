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

void MyFunction1(base::OnceCallback<int(std::string, double)> my_callback) {
  // OnceCallback
  int result1 = std::move(my_callback).Run("my string 1", 1.0);

  // After running a OnceCallback, it's consumed and nulled out.
  DCHECK(!my_callback)
}

void MyFunction2(base::RepeatingCallback<int(std::string, double)> my_callback) {
  int result1 = my_callback.Run("my string 1", 1.0);

  // Run() can be called as many times as you wish for RepeatingCallback.
  int result2 = my_callback.Run("my string 2", 2);
}

int main(int argc, char* argv[]) {

  return 0;
}