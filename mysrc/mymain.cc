#include <base/cpu.h>
#include <iostream>

int main2() {
  std::cout << "MYMAIN!" << std::endl;

  base::CPU cpu;
  std::cout << "has_sse:" << cpu.has_sse() << std::endl;

  std::cout << "has_avx:" << cpu.has_avx() << std::endl;
  return 0;
}

int main() {
  main2();

  return 0;
}