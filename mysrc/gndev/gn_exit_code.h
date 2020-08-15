// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef AMBIESOFT_GNDEV_EXIT_CODE_H_
#define AMBIESOFT_GNDEV_EXIT_CODE_H_

namespace ambiesoft {
namespace gndev {

enum class GndevExitCode {
  // Comparison succeeded.
  kSucceeded = 0,
  // Screenshot image empty.
  kImageEmpty,
  // Comparison failed.
  kFailed,
  // No comparison attempted.
  kNone,
};

}  // namespace gndev
}  // namespace ambiesoft

#endif  // AMBIESOFT_GNDEV_EXIT_CODE_H_
