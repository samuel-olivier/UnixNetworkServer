/*
** client.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:01:06 2015 Samuel Olivier
** Last update Tue Apr 21 18:06:41 2015 Samuel Olivier
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
int	client_read(client *this);
int	client_write(client *this);

#endif
