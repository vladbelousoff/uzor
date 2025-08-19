#pragma once

#include <stddef.h>

#ifdef UZ_DEBUG
#include "uz_list.h"
#endif

#ifdef UZ_DEBUG

typedef struct {
  const char* file;
  size_t line;
} uz_source_location_t;

typedef struct {
  uz_list_entry_t link;
  uz_source_location_t source_location;
  size_t buffer_size;
} uz_memory_header_t;

#define UZ_SOURCE_LOCATION                                                     \
  (uz_source_location_t)                                                       \
  {                                                                            \
    .file = __FILE__, .line = __LINE__                                         \
  }

#else

typedef int uz_source_location_t;
#define UZ_SOURCE_LOCATION 0

#endif

long uz_memory_init();
void uz_memory_free();

void* uz_new(size_t size, uz_source_location_t source_location);
void uz_free(void* memory);