#include "common/format.h"
#include "common/print.h"
#include "common/result.h"

using lr6::Unwrap;

int main() {
  lr6::PrintLine("This is {0}!", lr6::Red(42));

  return 0;
}