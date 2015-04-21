/*
** client.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:01:06 2015 Samuel Olivier
** Last update Tue Apr 21 17:51:12 2015 Samuel Olivier
*/

#ifndef __SERVER__
#define __SERVER__

#include <netinet/in.h>
#include <sys/time.h>

#include "list.h"
#include "client.h"

typedef struct
{
  int			socket;
  struct sockaddr_in	addr;
  list			clients;
}			server;

typedef void	*(*server_newClientCallback)(client *client, void *param);

server	*new_server();
void	delete_server(server *this);

void	server_listen(server *this, int port, int maxClientNumber);
int	server_flushNetwork(server *this, struct timeval *timeout,
			    server_newClientCallback newClientCallback,
			    void *param);

#endif
