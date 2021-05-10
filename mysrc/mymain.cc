#include <iostream>

#include "base/cpu.h"
#include "base/logging.h"



int main3() {
  int i = 3;
  DCHECK(i == 3);
  DCHECK(i == 4);

  LAZY_STREAM(LOG_STREAM(DCHECK), !ANALYZER_ASSUME_TRUE(true))
      << "Check failed: "
         "true"
         ". ";

  LAZY_STREAM(COMPACT_GOOGLE_LOG_EX_DCHECK(LogMessage).stream(),
              !ANALYZER_ASSUME_TRUE(true))
      << "Check failed: "
         "true"
         ". ";

  LAZY_STREAM(COMPACT_GOOGLE_LOG_EX_DCHECK(LogMessage).stream(),
              !ANALYZER_ASSUME_TRUE(true))
      << "Check failed: "
         "true"
         ". ";

  !(true) ? (void)0
          : ::logging::LogMessageVoidify() &
                (COMPACT_GOOGLE_LOG_EX_DCHECK(LogMessage).stream());

  return 0;
}
int main2() {
  std::cout << "MYMAIN!" << std::endl;

  base::CPU cpu;
  std::cout << "has_sse:" << cpu.has_sse() << std::endl;

  std::cout << "has_avx:" << cpu.has_avx() << std::endl;
  return 0;
}

int main() {
//  main3();
  main2();

  return 0;
}