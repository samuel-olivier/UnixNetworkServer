/*
** main.c for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 13:28:00 2015 Samuel Olivier
** Last update Tue Apr 21 18:55:01 2015 Samuel Olivier
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int	check_commands(server *server)
{
  return 0;
}

int	main(int ac, char **av)
{
  if (ac != 2) {
    printf("Usage: %s port\n", av[0]);
    return 1;
  }
  server	*server = new_server();
  int		stop = 0;

  server_listen(server, atoi(av[1]), 10);
  while (!stop) {
    server_flushNetwork(server, NULL, NULL, NULL);
    stop = check_commands(server);
  }
  delete_server(server);
  return 0;
}
