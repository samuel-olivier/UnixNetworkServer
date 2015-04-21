/*
** list.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:04:13 2015 Samuel Olivier
** Last update Tue Apr 21 13:29:27 2015 Samuel Olivier
*/

#ifndef __LIST__
#define __LIST__

typedef struct		s_listItem
{
  void			*data;
  struct s_listItem	*next;
}			listItem;

typedef listItem* list;
typedef void (*list_foreachFunction)(int idx, void *data, void *param);

list	new_list();

void	list_append(list *this, void *data);
void	list_prepend(list *this, void *data);
int	list_length(list *this);
void	list_foreach(list *this, list_foreachFunction func, void *param);

#endif
