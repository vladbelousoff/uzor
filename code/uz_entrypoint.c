#include "uz_memory.h"

int main(void)
{
  if (uz_memory_init() != 0) {
    return 1;
  }

  uz_memory_free();
  return 0;
}
