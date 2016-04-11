/*
** main.c for  in /home/querat_g/tmp/PSU_2015_strace/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Apr  5 10:03:57 2016 querat_g
** Last update Sun Apr 10 17:10:08 2016 querat_g
*/

#include "strace.h"
#include "syscall.h"

static t_trace	*g_opt = NULL;

void	handle_sig(int sig)
{
  if (sig == SIGINT)
    {

      if ((ptrace(PTRACE_CONT, g_opt->child_pid, 0, 0)) == -1)
	perror("handle_sig");
      if ((ptrace(PTRACE_DETACH, g_opt->child_pid, 0, 0)) == -1)
	perror("handle_sig");

      fprintf(stderr, "Process %d detached\n", g_opt->child_pid);
      exit(g_opt->child_status);
    }
}

int	strace_parent(t_trace *opt)
{
  bool	is_a_syscall;

  waitpid(opt->child_pid, &opt->child_status, 0);

  while ((!WIFEXITED(opt->child_status)))
    {
      is_a_syscall = false;

      if ((ptrace(PTRACE_GETREGS, opt->child_pid, 0, &opt->reg)) == -1)
      	return (my_perror("strace_parent"), 1);

      is_a_syscall = is_syscall(opt);

      if ((ptrace(PTRACE_SINGLESTEP, opt->child_pid, 0, 0)) == -1)
	return (my_perror("strace_parent"), 1);
      waitpid(opt->child_pid, &opt->child_status, 0);

      if (is_a_syscall)
	dump_syscall(opt);
    }
  return (EXIT_SUCCESS);
}

int	strace_fork(t_trace *opt)
{
  pid_t	pid;

  pid = fork();
  if (pid == -1)
    {
      fprintf(stderr, "strace_fork(): error: %s\n", strerror(errno));
      return (EXIT_FAILURE);
    }

  opt->is_parent = pid ? true : false;
  opt->child_pid = pid;

  if (opt->is_parent)
    return (strace_parent(opt));
  else
    {
      if ((ptrace(PTRACE_TRACEME, 0, 0, 0)) == -1)
	return (perror(strerror(errno)), 1);
      kill(getpid(), SIGSTOP);
      return (execvp(opt->argv[0], opt->argv));
    }

  return (opt->child_status);
}

int	strace_attach(t_trace *opt)
{
  bool	is_a_syscall;

  if ((ptrace(PTRACE_ATTACH, opt->child_pid, 0, 0)) == -1)
    return (perror("strace_attach PTRACE_ATTACH"), 1);
  usleep(1);
  waitpid(opt->child_pid, &opt->child_status, 0);

  while (!(WIFEXITED(opt->child_status)))
    {
      is_a_syscall = false;

      if ((ptrace(PTRACE_GETREGS, opt->child_pid, 0, &opt->reg)) == -1)
      	return (my_perror("strace_parent"), 1);

      is_a_syscall = is_syscall(opt);

      if ((ptrace(PTRACE_SINGLESTEP, opt->child_pid, 0, 0)) == -1)
	return (my_perror("strace_parent"), 1);
      waitpid(opt->child_pid, &opt->child_status, 0);

      if (is_a_syscall)
	dump_syscall(opt);
    }

    return (opt->child_status);
}

int	main(int ac , char **argv)
{
  t_trace	opt;
  int		ret;

  ret = 0;
  if (ac < 2)
    {
      fprintf(stderr, "Usage : %s [-s] [-p <pid>|<command>]\n", argv[0]);
      return (EXIT_FAILURE);
    }
  if (!t_trace_const(&opt, ac, argv))
    return (t_trace_dest(&opt), EXIT_FAILURE);

  if (opt.attached_pid)
    {
      g_opt = &opt;
      opt.child_pid = opt.attached_pid;
      signal(SIGINT, &handle_sig);
      ret = strace_attach(&opt);
    }
else
    ret = strace_fork(&opt);

  fprintf(stderr, "+++ exited with %d +++\n", ret);
  t_trace_dest(&opt);
  return (EXIT_SUCCESS);
}
