/*
** syscall.h for  in /home/querat_g/tmp/syscall
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Apr  8 14:02:51 2016 querat_g
** Last update Fri Apr  8 14:32:12 2016 querat_g
*/

#ifndef SYSCALL_H_
# define SYSCALL_H_

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct s_syscall
{
  int		id;
  char		*name;
  int		nb_params;
  bool		return_type;
}		t_syscall;

#endif /* !syscall.h */
