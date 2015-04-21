/*
** list.h for  in /home/olivie_f/dev/network
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Tue Apr 21 11:04:13 2015 Samuel Olivier
** Last update Tue Apr 21 19:28:45 2015 Samuel Olivier
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
typedef int (*list_removeIfFunction)(int idx, void *data, void *param);
typedef void (*list_deleteFunction)(void *data);

list	new_list();
void	delete_list(list *this, list_deleteFunction funcPtr);

void	list_append(list *this, void *data);
void	list_prepend(list *this, void *data);
int	list_length(list *this);
void	list_foreach(list *this, list_foreachFunction funcPtr, void *param);
int	list_removeIf(list *this, list_removeIfFunction funcPtr, void *param);

#endif
