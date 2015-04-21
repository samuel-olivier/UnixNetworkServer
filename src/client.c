/*
** client.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 17:40:18 2015 Samuel Olivier
** Last update Tue Apr 21 20:30:59 2015 Samuel Olivier
*/

#include "client.h"

#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

client  *new_client()
{
  client	*res = malloc(sizeof(*res));

  res->socket = -1;
  bzero(&res->addr, sizeof(res->addr));
  res->read = new_buffer();
  res->write = new_buffer();
  res->data = NULL;
  return res;
}

void    delete_client(client *this)
{
  if (this->socket >= 0) {
    close(this->socket);
  }
  delete_buffer(this->read);
  delete_buffer(this->write);
  free(this);
}

int	client_accept(client *this, int socket)
{
  socklen_t	len;

  len = sizeof(this->addr);
  this->socket = accept(socket, (struct sockaddr*)&(this->addr), &len);
  return this->socket == -1 ? 0 : 1;
}

int	client_flushRead(client *this)
{
  char	buffer[CLIENT_READ_SIZE];
  int	nbRead = read(this->socket, buffer, CLIENT_READ_SIZE);

  if (nbRead < 0) {
    perror("read()");
    return -1;
  } else if (nbRead == 0) {
    printf("[DEBUG] Client closed the connection : fd = %d\n", this->socket);
    close(this->socket);
    this->socket = -1;
    return 0;
  }
  buffer_append(this->read, buffer, nbRead);
  return nbRead;
}

int	client_flushWrite(client *this)
{
  int	sizeToWrite = buffer_size(this->write) > CLIENT_WRITE_SIZE ?
    CLIENT_WRITE_SIZE : buffer_size(this->write);
  int	nbWriten = write(this->socket, buffer_data(this->write), sizeToWrite);

  if (nbWriten < 0) {
    perror("write()");
    return -1;
  }
  buffer_remove(this->write, nbWriten);
  return nbWriten;

}

void	client_writeData(client *this, char *data, int size)
{
  buffer_append(this->write, data, size);
}

void	client_writeString(client *this, char *str)
{
  client_writeData(this, str, strlen(str));
}
