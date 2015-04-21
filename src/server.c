/*
** server.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 17:02:50 2015 Samuel Olivier
** Last update Tue Apr 21 20:18:59 2015 Samuel Olivier
*/

#include "server.h"

#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
  fd_set	readFdSet;
  fd_set	writeFdSet;
  int		maxFd;
}		fdSetContainer;

static void	initFdSets(server *this, fdSetContainer *fdSets);
static void	flushNetworkForOneClient(int idx, void *data, void *param);
static int	clientNeedDeletion(int idx, void *data, void *param);
static void	deleteOneClient(void *data);

server	*new_server()
{
  server	*res = malloc(sizeof(*res));

  bzero(res, sizeof(*res));
  res->socket = -1;
  res->clients = new_list();
  return res;
}

void	delete_server(server *this)
{
  delete_list(&this->clients, &deleteOneClient);
  if (this->socket >= 0) {
    close(this->socket);
  }
  free(this);
}

void    server_listen(server *this, int port, int maxClientNumber)
{
  this->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->socket == -1) {
    perror("socket()");
    delete_server(this);
    return ;
  }
  int yes = 1;
  if (setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR,
		 &yes, sizeof(int)) == -1 ) {
    perror("setsockopt()");
  }
  this->addr.sin_family = AF_INET;
  this->addr.sin_addr.s_addr = INADDR_ANY;
  this->addr.sin_port = htons(port);
  if (bind(this->socket, (struct sockaddr *)&(this->addr),
	   sizeof(this->addr)) < 0) {
    this->addr.sin_port = htons(0);
    if (bind(this->socket, (struct sockaddr *)&(this->addr),
	     sizeof(this->addr)) < 0) {
      perror("bind()");
      delete_server(this);
      return ;
    }
  }
  if (listen(this->socket, maxClientNumber) == -1) {
    perror("listen()");
    delete_server(this);
    return ;
  }
  struct sockaddr_in	addr;
  socklen_t		addr_len = sizeof(addr);

  getsockname(this->socket, (struct sockaddr*)&addr, &addr_len);
  printf("[DEBUG] Server listenning on port %d\n", ntohs(addr.sin_port));
}

int	server_flushNetwork(server *this, struct timeval *timeout,
                            server_newClientCallback newClientCallback,
			    void *param)
{
  fdSetContainer	fdSets;

  list_removeIf(&this->clients, clientNeedDeletion, NULL);
  initFdSets(this, &fdSets);
  if (select(fdSets.maxFd + 1, &fdSets.readFdSet, &fdSets.writeFdSet,
	     NULL, timeout) == -1) {
    perror("select()");
    return 0;
  }
  if (FD_ISSET(this->socket, &fdSets.readFdSet)) {
    client	*client = new_client();

    if (client_accept(client, this->socket)) {
      if (newClientCallback != NULL) {
	client->data = newClientCallback(client, param);
      } else {
	client->data = NULL;
      }
      list_append(&this->clients, client);
      printf("[DEBUG] New client : fd = %d\n", client->socket);
    } else {
      delete_client(client);
    }
  }
  list_foreach(&this->clients, &flushNetworkForOneClient, &fdSets);
  return 1;
}

static void	deleteOneClient(void *data)
{
  client		*client = data;

  delete_client(client);
}

static int	clientNeedDeletion(int idx, void *data, void *param)
{
  client		*client = data;

  (void)idx;
  (void)param;
  if (client->socket == -1) {
    delete_client(client);
    return 1;
  }
  return 0;
}

static void	flushNetworkForOneClient(int idx, void *data, void *param)
{
  client		*client = data;
  fdSetContainer	*fdSets = param;

  (void)idx;
  if (FD_ISSET(client->socket, &fdSets->readFdSet)) {
    client_flushRead(client);
  }
  if (!buffer_isEmpty(client->write) &&
      FD_ISSET(client->socket, &fdSets->writeFdSet)) {
    client_flushWrite(client);
  }
}

static void	initFdSetsForOneClient(int idx, void *data, void *param)
{
  client		*client = data;
  fdSetContainer	*fdSets = param;

  (void)idx;
  FD_SET(client->socket, &fdSets->readFdSet);
  if (!buffer_isEmpty(client->write)) {
    FD_SET(client->socket, &fdSets->writeFdSet);
  }
  if (client->socket > fdSets->maxFd) {
    fdSets->maxFd = client->socket;
  }
}

static void	initFdSets(server *this, fdSetContainer *fdSets)
{
  FD_ZERO(&fdSets->readFdSet);
  FD_ZERO(&fdSets->writeFdSet);  

  FD_SET(this->socket, &fdSets->readFdSet);
  fdSets->maxFd = this->socket;
  list_foreach(&this->clients, &initFdSetsForOneClient, fdSets);
}
