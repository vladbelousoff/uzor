#include "uz_memory.h"

#include "uz_log.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef UZ_DEBUG_BUILD
#include <threads.h>
#endif

#ifdef UZ_DEBUG_BUILD
static mtx_t mem_mtx;
static uz_list_head_t mem_allocs;
#endif

long uz_memory_init()
{
#ifdef UZ_DEBUG_BUILD
  if (mtx_init(&mem_mtx, mtx_plain) != thrd_success) {
    return 1;
  }
  uz_list_init(&mem_allocs);
#endif
  return 0;
}

void uz_memory_free()
{
#ifdef UZ_DEBUG_BUILD
  uz_list_entry_t* entry;
  uz_list_entry_t* tmp;
  uz_list_for_each_safe(entry, tmp, &mem_allocs)
  {
    uz_memory_header_t* header =
      uz_list_record(entry, uz_memory_header_t, link);
    uz_log_err("Leaked memory, file: %s, line: %llu, size: %llu",
               uz_filename(header->source_location.file),
               header->source_location.line, header->buffer_size);
    uz_list_remove(&header->link);
    free(header);
  }

  mtx_destroy(&mem_mtx);
#endif
}

void* uz_malloc(const size_t size, const uz_source_location_t source_location)
{
#if UZ_DEBUG_BUILD
  // ReSharper disable once CppDFAMemoryLeak
  char* data = malloc(size + sizeof(uz_memory_header_t));
  if (data) {
    uz_memory_header_t* header = (uz_memory_header_t*)data;
    header->source_location = source_location;
    header->buffer_size = size;
    mtx_lock(&mem_mtx);
    uz_list_add_tail(&mem_allocs, &header->link);
    mtx_unlock(&mem_mtx);
    // ReSharper disable once CppDFAMemoryLeak
    return &data[sizeof(uz_memory_header_t)];
  }
  return data;
#else
  (void)source_location;
  return malloc(size);
#endif
}

void* uz_realloc(void* memory, const size_t size,
                 const uz_source_location_t source_location)
{
#if UZ_DEBUG_BUILD
  uz_memory_header_t* header =
    (uz_memory_header_t*)((char*)memory - sizeof(uz_memory_header_t));
  header->source_location = source_location;
  header->buffer_size = size;
  return realloc(memory, size + sizeof(uz_memory_header_t));
#else
  (void)source_location;
  return realloc(memory, size);
#endif
}

void uz_free(void* memory)
{
#if UZ_DEBUG_BUILD
  uz_memory_header_t* header =
    (uz_memory_header_t*)((char*)memory - sizeof(uz_memory_header_t));
  uz_list_remove(&header->link);
  free(header);
#else
  free(memory);
#endif
}