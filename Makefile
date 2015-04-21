##
## Makefile for  in /home/olivie_f/dev/network
## 
## Made by Samuel Olivier
## Login   <olivie_f@epitech.net>
## 
## Started on  Tue Apr 21 13:27:49 2015 Samuel Olivier
## Last update Tue Apr 21 17:49:06 2015 Samuel Olivier
##

NAME	= test

CC	= gcc

RM	= rm -f

CFLAGS	= -W -Wall -I include -std=c99 -g

LDFLAGS	= 

SRC	= src/main.c \
	  src/list.c \
	  src/buffer.c \
	  src/server.c \
	  src/client.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
