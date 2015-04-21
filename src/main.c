/*
** main.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 13:28:00 2015 Samuel Olivier
** Last update Tue Apr 21 20:41:42 2015 Samuel Olivier
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "server.h"

static int	g_stop = 0;

int	firstIndexOf(char *str, int size, char c)
{
  if (str == NULL || size <= 0) {
    return -1;
  }
  char *first = memchr(str, c, size);
  return (first == NULL) ? -1 : (first - str);
}

static void	sendToAllClients(int idx, void *data, void *param)
{
  client	*client = data;
  char		*msg = param;

  (void)idx;
  client_writeString(client, msg);
}

static void	printLines(int idx, void *data, void *param)
{
  client	*client = data;
  server	*server = param;
  (void)idx;

  int first;
  while ((first = firstIndexOf(buffer_data(client->read),
			       buffer_size(client->read), '\n')) != -1) {
    ++first;
    char *line = buffer_pop(client->read, &first);

    line[first - 1] = '\0';
    char buf[first + 100];
    snprintf(buf, first + 100, "Received from %d : '%s'\n",
	     client->socket, line);
    list_foreach(&server->clients, &sendToAllClients, buf);
  }
}

static void	check_commands(server *server)
{
  list_foreach(&server->clients, &printLines, server);
}

void	quit()
{
  g_stop = 1;
}

void	handleSignal(int sig)
{
  (void)sig;
  quit();
}

int	main(int ac, char **av)
{
  if (ac != 2) {
    printf("Usage: %s port\n", av[0]);
    return 1;
  }

  server *server = new_server();
  signal(SIGINT, &quit);
  server_listen(server, atoi(av[1]), 10);
  while (!g_stop) {
    server_flushNetwork(server, NULL, NULL, NULL);
    check_commands(server);
  }
  printf("[DEBUG] Exiting...\n");
  delete_server(server);
  return 0;
}
