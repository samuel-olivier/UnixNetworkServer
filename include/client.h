/*
** client.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:01:06 2015 Samuel Olivier
** Last update Tue Apr 21 20:21:16 2015 Samuel Olivier
*/

#ifndef __CLIENT__
#define __CLIENT__

#include <netinet/in.h>

#include "buffer.h"

#define CLIENT_READ_SIZE 1024
#define CLIENT_WRITE_SIZE 1024


typedef struct
{
  int			socket;
  struct sockaddr_in	addr;
  buffer		*read;
  buffer		*write;
  void			*data;
}			client;

client	*new_client();
void	delete_client(client *this);

int	client_accept(client *this, int socket);
int	client_flushRead(client *this);
int	client_flushWrite(client *this);
void	client_writeData(client *this, char *data, int size);
void	client_writeString(client *this, char *str);

#endif
