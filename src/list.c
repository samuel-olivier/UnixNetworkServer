/*
** list.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:06:54 2015 Samuel Olivier
** Last update Tue Apr 21 19:29:41 2015 Samuel Olivier
*/

#include "list.h"

#include <unistd.h>
#include <stdlib.h>

static listItem	*list_newItem(void *data);

list	new_list()
{
  return NULL;
}

void    delete_list(list *this, list_deleteFunction funcPtr)
{
  listItem	*it = *this;
  listItem	*current = NULL;

  while (it != NULL) {
    if (funcPtr != NULL) {
      funcPtr(it->data);
    }
    current = it;
    it = it->next;
    free(current);
  }
}

void		list_append(list *this, void *data)
{
  listItem	*item = list_newItem(data);

  if (*this == NULL) {
    *this = item;
    return ;
  }

  listItem	*it = *this;
  while (it->next != NULL) {
    it = it->next;
  }
  it->next = item;
}

void	list_prepend(list *this, void *data)
{
  listItem *item = list_newItem(data);

  item->next = *this;
  *this = item;
}

int	list_length(list *this)
{
  listItem *it = *this;
  int length = 0;

  while (it != NULL) {
    it = it->next;
    ++length;
  }
  return length;
}

void	list_foreach(list *this, list_foreachFunction funcPtr, void *param)
{
  if (funcPtr == NULL) {
    return ;
  }
  listItem	*it = *this;
  int		idx = 0;

  while (it != NULL) {
    funcPtr(idx, it->data, param);
    it = it->next;
    ++idx;
  }
}

int	list_removeIf(list *this, list_removeIfFunction funcPtr, void *param)
{
  if (funcPtr == NULL) {
    return 0;
  }
  listItem	*it = *this;
  listItem	*prev = NULL;
  int		idx = 0;
  int		nbRemoved = 0;

  while (it != NULL) {
    if (funcPtr(idx, it->data, param)) {
      listItem	*current = it;

      if (prev == NULL) {
	*this = current->next;
      } else {
	prev->next = current->next;
      }
      it = it->next;
      free(current);
      ++nbRemoved;
    } else {
      prev = it;
      it = it->next;
      ++idx;
    }
  }
  return nbRemoved;
}

static listItem*	list_newItem(void* data)
{
  listItem*	item = malloc(sizeof(*item));

  item->next = NULL;
  item->data = data;
  return item;
}
