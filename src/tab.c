/*
** tab.c for  in /home/querat_g/tmp/PSU_2015_strace
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Apr  8 14:19:49 2016 querat_g
** Last update Fri Apr  8 15:31:24 2016 querat_g
*/

#include "syscall.h"

/*
** contains the array of t_syscall
** under the following format :
**     static const t_syscall g_syscall[]
*/
#include "syscalls_tab.h"

bool	syscall_exists(int id)
{
  int	i;

  i = 0;
  while (g_syscall[i].id != -1)
    {
      if (g_syscall[i].id == id)
	return (true);
      ++i;
    }
  return (false);
}

t_syscall const	*get_t_syscall(int id)
{
  int	i;

  i = 0;
  while (g_syscall[i].id != -1)
    {
      if (g_syscall[i].id == id)
	return (&g_syscall[i]);
      ++i;
    }
  return (NULL);
}
