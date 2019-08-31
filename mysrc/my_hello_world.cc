// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <iostream>

#include "base/logging.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, world!" << std::endl;

  // Use of LOG is more common than raw std::cout.
  LOG(INFO) << "Hello, logging!";
}