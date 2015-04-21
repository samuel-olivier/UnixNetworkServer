/*
** buffer.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 13:42:08 2015 Samuel Olivier
** Last update Tue Apr 21 18:26:49 2015 Samuel Olivier
*/

#include "buffer.h"

#include <stdlib.h>
#include <string.h>

buffer	*new_buffer()
{
  buffer	*this = malloc(sizeof(*this));

  this->data = NULL;
  this->size = 0;
  return this;
}

void	delete_buffer(buffer *this)
{
  if (this->data != NULL) {
    free(this->data);
  }
  free(this);
}

void	buffer_append(buffer *this, char *data, int size)
{
  if (size <= 0 || data == NULL) {
    return ;
  }
  this->data = realloc(this->data, sizeof(*this->data) * (this->size + size));
  memcpy(&this->data[this->size], data, size);
  this->size += size;
}

int	buffer_remove(buffer *this, int size)
{
  if (size <= 0 || this->data == NULL) {
    return -1;
  }
  if (size > this->size) {
    size = this->size;
  }
  memmove(this->data, &this->data[size], this->size - size);
  this->size -= size;
  this->data = realloc(this->data, sizeof(*this->data) * (this->size));
  return size;
}

char	*buffer_pop(buffer *this, int *size)
{
  if (size == NULL || *size <= 0 || this->data == NULL) {
    return NULL;
  }
  if (*size > this->size) {
    *size = this->size;
  }
  char	*res = malloc(sizeof(*res) * *size);

  memcpy(res, this->data, *size);
  memmove(this->data, &this->data[*size], this->size - *size);
  this->size -= *size;
  this->data = realloc(this->data, sizeof(*this->data) * (this->size));
  return res;
}

int	buffer_size(buffer *this)
{
  return this->size;
}

char	*buffer_data(buffer *this)
{
  return this->data;
}

int	buffer_isEmpty(buffer *this)
{
  return buffer_size(this) <= 0;
}
