/*
** t_trace.c for  in /home/querat_g/tmp/PSU_2015_strace/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Apr  5 14:58:00 2016 querat_g
** Last update Wed Apr  6 10:16:08 2016 querat_g
*/

#include "strace.h"

bool	is_trace(char *s)
{
  return (s && s[0] == '-');
}

int	get_num(char *str)
{
  int	i;

  i = -1;
  if (!str || !str[0])
    {
      fprintf(stderr, "No string after -p ! there should be a number !\n");
      return (-1);
    }
  while (str[++i])
    {
      if (str[i] < '0' || str[i] > '9')
	{
	  fprintf(stderr, "argument after -p must be an unsigned number.\n");
	  return (-1);
	}
    }
  return (atoi(str));
}

bool	get_s_trace(t_trace *opt, char **argv)
{
  int	i;

  i = 0;
  while (argv[++i])
    {
      if (!strcmp(argv[i], "-s"))
	opt->flags |= S_FLAG;
    }
  return (true);
}

bool	get_argv(t_trace *opt, int ac, char **argv)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (!(opt->argv = calloc((ac + 1), (sizeof(char*)))))
    return (fprintf(stderr, "get_argv(): malloc failed\n"));

  while (argv[++i] && is_trace(argv[i]));

  if (!argv[i])
    return (false);

  while (argv[i])
    opt->argv[j++] = argv[i++];
  opt->ac = j;

  return (true);
}

bool	get_p_opt(t_trace *opt, char **argv) {
  int	i;
  bool	after_argv;

  i = 0;
  after_argv = false;
  while (argv[++i])
    {
      if (!strncmp(argv[i], "-p", 2) && !after_argv)
	{
	  if ((strlen(argv[i]) > 2))
	    {
	      if ((opt->attached_pid = get_num(&argv[i][2])) < 0)
		{
		  opt->err_code = true;
		  return (true);
		}
	    }
	  else
	    {
	      if ((opt->attached_pid = get_num(argv[++i])) < 0)
		{
		  opt->err_code = true;
		  return (true);
		}
	    }
	}
      else if (strcmp(argv[i], "-s"))
	after_argv = true;
    }
  return (false);
}
