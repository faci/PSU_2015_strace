##
## Makefile for  in /home/querat_g/PSU_2015_strace/src
## 
## Made by querat_g
## Login   <querat_g@epitech.net>
## 
## Started on  Mon Apr  4 09:53:04 2016 querat_g
## Last update Sun Apr 10 17:26:39 2016 querat_g
##

CC		=	gcc

NAME		=	strace

SRCS		=	src/main.c \
			src/t_opt.c \
			src/get_opt.c \
			src/tab.c \
			src/dump.c \
			src/is_syscall.c

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Wextra -I./include
CFLAGS		+=	-I./include/
CFLAGS		+=	-I./syscall/

LDFLAGS		=

all:			$(NAME)

$(NAME):		$(OBJS)
			@`which echo` "-e" "\n\e[1;37m"now linking $(NAME) ..."\e[0m"
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

.c.o:
			@`which echo` -ne "\e[1;36m"$@"\t""\e[0m"
			$(CC) -c -o $@ $(CFLAGS) $<

clean:
			rm -f $(OBJS)

fclean:			clean
			rm -f $(NAME)

re:			fclean all

.PHONY:			all clean fclean re .c.o
