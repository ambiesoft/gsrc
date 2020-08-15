// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_GNDEV_MAIN_PROC_H_
#define AMBIESOFT_GNDEV_MAIN_PROC_H_

#include "gn_exit_code.h"

namespace ambiesoft {
namespace gndev {

GndevExitCode GndevMainProc(bool under_test = false);

}  // namespace gndev
}  // namespace ambiesoft

#endif  // AMBIESOFT_GNDEV_MAIN_PROC_H_
