/*
** strace.h for  in /home/querat_g/PSU_2015_strace/src
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Apr  4 09:57:22 2016 querat_g
** Last update Sun Apr 10 17:11:02 2016 querat_g
*/

#ifndef STRACE_H_
# define STRACE_H_

# include <sys/ptrace.h>
# include <sys/wait.h>

# include <unistd.h>
# include <errno.h>
# include <signal.h>

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

# include "syscall.h"

# define R15	0
# define R14	1
# define R13	2
# define R12	3
# define RBP	4
# define RBX	5
# define R11	6
# define R10	7
# define R9	8
# define R8	9
# define RAX	10
# define RCX	11
# define RDX	12
# define RSI	13
# define RDI	14
# define ORIG_RAX 15
# define RIP	16
# define CS	17
# define EFLAGS	18
# define RSP	19
# define SS	20
# define FS_BASE 21
# define GS_BASE 22
# define DS	23
# define ES	24
# define FS	25
# define GS	26

/*
** include of /usr/include
** wouldn't compile on the merdinette so i'll just be a lazy ass
** and copy paste the header file in there
*/
struct user_regs_struct
{
  unsigned long long int r15;
  unsigned long long int r14;
  unsigned long long int r13;
  unsigned long long int r12;
  unsigned long long int rbp;
  unsigned long long int rbx;
  unsigned long long int r11;
  unsigned long long int r10;
  unsigned long long int r9;
  unsigned long long int r8;
  unsigned long long int rax;
  unsigned long long int rcx;
  unsigned long long int rdx;
  unsigned long long int rsi;
  unsigned long long int rdi;
  unsigned long long int orig_rax;
  unsigned long long int rip;
  unsigned long long int cs;
  unsigned long long int eflags;
  unsigned long long int rsp;
  unsigned long long int ss;
  unsigned long long int fs_base;
  unsigned long long int gs_base;
  unsigned long long int ds;
  unsigned long long int es;
  unsigned long long int fs;
  unsigned long long int gs;
};

typedef struct user_regs_struct	t_reg;

# define S_FLAG			0b01
# define P_FLAG			0b10
# define INSTRUCTION_MASK	0x000000000000FFFF
# define INSTRUCTION_OPCODE	0xCD80
# define MASK(x)		((x & INSTRUCTION_MASK))

typedef struct	s_trace
{
  bool		err_code;
  int		flags;
  pid_t		attached_pid;

  char		**argv;
  int		ac;

  bool		is_parent;
  pid_t		child_pid;

  int		child_status;

  t_reg		reg;
}		t_trace;

/*
** main.c
*/
int	main(int ac, char **av);
void	print_tab(char **tab);

/*
** t_trace.c
*/
bool	t_trace_dest(t_trace *opt);
bool	t_trace_const(t_trace *opt, int ac, char **argv);

/*
** get_trace.c
*/
bool	is_trace(char *s);
int	get_num(char *str);
bool	get_s_trace(t_trace *opt, char **argv);
bool	get_argv(t_trace *opt, int ac, char **argv);
bool	get_p_opt(t_trace *opt, char **argv);

/*
** tab.c
*/
bool		syscall_exists(int id);
t_syscall const *get_t_syscall(int id);

/*
** dump.c
*/
void		my_perror(char *name);
long long int	correct_neg(long long int nb);
bool		dump_regs(t_trace *opt, t_syscall const *sys);
bool		dump_syscall(t_trace *opt);

/*
** is_syscall.c
*/
bool	is_syscall(t_trace *opt);

#endif /* !strace.h */
