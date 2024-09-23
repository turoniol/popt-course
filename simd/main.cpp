#include "task1.h"
#include "task2.h"

#include <iomanip>
#include <iostream>

#ifndef __unix__
#error "Unsupported platform. Consider using OS with POSIX API."
#endif

int main() {
  std::cout << std::setprecision(7) << std::fixed;

  // run_task1();
  run_task2();
}