/*
** client.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:01:06 2015 Samuel Olivier
** Last update Tue Apr 21 18:25:55 2015 Samuel Olivier
*/

#ifndef __BUFFER__
#define __BUFFER__

typedef struct
{
  char		*data;
  int		size;
}		buffer; 

buffer	*new_buffer();
void	delete_buffer(buffer *this);

void	buffer_append(buffer *this, char *data, int size);
int	buffer_remove(buffer *this, int size);
char	*buffer_pop(buffer *this, int *size);

char	*buffer_data(buffer *this);
int	buffer_size(buffer *this);
int	buffer_isEmpty(buffer *this);

#endif
