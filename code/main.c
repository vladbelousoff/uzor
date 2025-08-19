#include "uz_log.h"

#include <stdio.h>
#include <string.h>

#include "uz_memory.h"

int main(void)
{
  if (uz_memory_init() != 0) {
    return 1;
  }

  char* string = uz_new(128, UZ_SOURCE_LOCATION);
  strcpy(string, "Hello World");
  uz_log_dbg("%s", string);

  // uz_free(string);

  uz_memory_free();
  return 0;
}
