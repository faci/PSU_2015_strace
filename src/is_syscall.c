/*
** is_syscall.c for  in /home/querat_g/tmp/PSU_2015_strace
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Apr 10 17:09:56 2016 querat_g
** Last update Sun Apr 10 17:10:40 2016 querat_g
*/

#include "strace.h"

bool	is_syscall(t_trace *opt)
{
  unsigned short	rip;

  rip = ptrace(PTRACE_PEEKTEXT, opt->child_pid, opt->reg.rip, 0);
  if (rip == 0xFFFF)
    {
      my_perror("is_syscall()");
      exit(1);
    }
  if (rip == 0x80CD || rip == 0x50F)
      return (true);

  return (false);
}
