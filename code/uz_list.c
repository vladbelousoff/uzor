#include "uz_list.h"

static void uz_list_insert(uz_list_entry_t* _new, uz_list_entry_t* prev,
                           uz_list_entry_t* next)
{
  next->prev = _new;
  _new->next = next;
  _new->prev = prev;
  prev->next = _new;
}

void uz_list_init(uz_list_head_t* head)
{
  head->prev = head;
  head->next = head;
}

void uz_list_add_head(uz_list_head_t* head, uz_list_entry_t* entry)
{
  uz_list_insert(entry, head, head->next);
}

void uz_list_add_tail(uz_list_head_t* head, uz_list_entry_t* entry)
{
  uz_list_insert(entry, head->prev, head);
}

static void uz_list_remove2(uz_list_entry_t* prev, uz_list_entry_t* next)
{
  next->prev = prev;
  prev->next = next;
}

void uz_list_remove(const uz_list_entry_t* entry)
{
  uz_list_remove2(entry->prev, entry->next);
}

long uz_list_empty(const uz_list_entry_t* head)
{
  return head->next == head;
}
