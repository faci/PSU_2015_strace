/*
** dump.c for  in /home/querat_g/tmp/PSU_2015_strace/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sat Apr  9 10:24:44 2016 querat_g
** Last update Sat Apr  9 10:28:09 2016 querat_g
*/

#include "strace.h"

void	my_perror(char *name)
{
  fprintf(stderr, "%s(): %s\n", name, strerror(errno));
}

long long int		correct_neg(long long int nb)
{
  if (nb < 0)
    return (++nb);
  return (nb);
}

bool			dump_regs(t_trace *opt, t_syscall const *sys)
{
  if (sys->nb_params > 0)
    fprintf(stderr, "0x%llx", opt->reg.rdi);
  if (sys->nb_params > 1)
    fprintf(stderr, ", 0x%llx", opt->reg.rsi);
  if (sys->nb_params > 2)
    fprintf(stderr, ", 0x%llx", opt->reg.rdx);
  if (sys->nb_params > 3)
    fprintf(stderr, ", 0x%llx", opt->reg.r8);
  if (sys->nb_params > 4)
    fprintf(stderr, ", 0x%llx", opt->reg.r10);
  if (sys->nb_params > 5)
    fprintf(stderr, ", 0x%llx", opt->reg.r9);
  if (sys->return_type)
    {
      if ((ptrace(PTRACE_SINGLESTEP, opt->child_pid, 0, 0)) == -1)
	return (my_perror("dump_syscall"), false);
      waitpid(opt->child_pid, &opt->child_status, 0);
      if ((ptrace(PTRACE_GETREGS, opt->child_pid, 0, &opt->reg)) == -1)
	return (my_perror("strace_parent"), false);
      fprintf(stderr, ") = 0x%llx\n", correct_neg(opt->reg.rax));
    }
  else
    fprintf(stderr, ") = ?\n");
  return (true);
}

bool			dump_syscall(t_trace *opt)
{
  t_syscall const	*sys;

  sys = get_t_syscall((opt->reg.rax & 0X000000000000FFFF));
  if (!sys)
    return (false);
  fprintf(stderr, "%s(", sys->name);
  dump_regs(opt, sys);
  return (true);
}
