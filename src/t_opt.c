/*
** t_trace.c for  in /home/querat_g/tmp/PSU_2015_strace/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Apr  5 14:58:00 2016 querat_g
** Last update Tue Apr  5 14:58:24 2016 querat_g
*/

#include "strace.h"

bool	t_trace_dest(t_trace *opt)
{
  if (!opt)
    return (false);

  if (opt->argv)
    free(opt->argv);

  memset(opt, '\0', sizeof(t_trace));
  return (false);
}

bool	t_trace_const(t_trace *opt, int ac, char **argv)
{
  memset(opt, '\0', sizeof(t_trace));
  get_s_trace(opt, argv);
  if (get_p_opt(opt, argv))
    {
      if (opt->err_code)
	return (false);
      return (true);
    }
  else
    {
      if (!get_argv(opt, ac, argv))
	return (false);
    }
  return (true);
}
