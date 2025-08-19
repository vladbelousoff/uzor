#include "uz_log.h"
#include "uz_memory.h"

#include <stdio.h>

typedef struct {
  long (*init)(void);
  void (*free)(void);
  const char* name;
} uz_system;

#define UZ_ARRAY_SIZE(x)                                                       \
  _Generic(&(x), __typeof__(&(x)): (sizeof(x) / sizeof((x)[0])))

static uz_system systems[] = {
  { uz_memory_init, uz_memory_free, "Memory" },
};

static void free_systems_starting_from(const int index)
{
  for (int i = index; i >= 0; --i) {
    uz_log_dbg("Free system '%s'", systems[i].name);
    systems[i].free();
  }
}

static long init_systems(void)
{
  for (int i = 0; i < UZ_ARRAY_SIZE(systems); ++i) {
    uz_log_dbg("Init system '%s'", systems[i].name);
    if (systems[i].init() != 0) {
      free_systems_starting_from(i - 1);
      return 1;
    }
  }

  return 0;
}

static void free_systems(void)
{
  free_systems_starting_from(UZ_ARRAY_SIZE(systems) - 1);
}

int main(void)
{
  init_systems();
  free_systems();

  return 0;
}
