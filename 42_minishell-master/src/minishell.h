/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:13:37 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/26 09:35:40 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Pac4's libft
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
//The readline library may not come installed by default. The package on
//Ubuntu is called "libreadline-dev", while on Fedora it's
//"readline-devel".
# include <readline/readline.h>
# include <readline/history.h>

//Shell name
# define SHELL "MiniHell"

//Macro for print_shell_err() not quitting the program
# define NO_EXIT 69420

//Standard permissions for new files in Unix-based/like systems
//0 - special file permissions (none in this case)
//6 - user permissions (read + write)
//4 - group permissions (read)
//4 - others permissions (read)
# define S_STDPERMS 0644

//Node types
typedef enum e_ndtype
{
	E_ARG,
	E_PIPE,
	E_FLAG,
	E_STDIN,
	E_HDOC,
	E_STDOUT,
	E_APPEND,
	E_BUILTIN,
	E_CMD
}			t_ndtype;

//Input/Output (used for redirections)
typedef enum e_io
{
	E_IN,
	E_OUT
}			t_io;

//Signal types
typedef enum e_sigtype
{
	E_SIG_IGN,
	E_SIG_DFL,
	E_SIG_RL,
	E_SIG_HDOC
}			t_sigtype;

//Binary Tree struct (also known as Command Table)
typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*right;
	struct s_tree	*left;
	enum e_ndtype	type;
	char			*content;
	int				pipes[2];
	int				pipe_num;
	int				inter;
}			t_tree;

//Parser helper struct
typedef struct s_parse
{
	int		pos;
	int		*exp;
	char	**env;
	t_tree	**tree;
}			t_parse;

//Pipe struct used during parsing
typedef struct s_pipe
{
	int				pos;
	int				num;
	struct s_pipe	*next;
}			t_pipe;

//Exclusively used by add_var()
typedef struct s_var
{
	int		start;
	int		end;
	int		i;
	int		j;
	char	*str;
	char	*var;
	char	**res;
}			t_var;

//Command struct for the executor
typedef struct s_cmd
{
	pid_t	pid;
	int		pipes[2];
	int		pos;
	int		num;
	int		fd;
	int		in;
	int		out;
	int		heredoc;
	char	***env;
}			t_cmd;

//main.c
void			set_exit_stts(int stts);
char			*shlvl_up(char *shlvl);
//env_utils.c
char			**get_cur_env(char **env);
//exit_stts.c
int				*exit_stts(void);

/*					 PARSER						*/
//parser.c
void			parsa(char *in, char ***env, t_tree **root, int num);
//parser_utils.c
void			parse_all(t_tree **root, char *arg, t_pipe **pipes, int num);
//syntax_utils.c
int				*syntax(void);
//tree_init.c
void			tree_add_node(char *arg, t_ndtype type, t_parse parse);
void			tree_add_n_parse(t_tree **node, char *arg, t_ndtype type);
//tree_utils.c
void			tree_add_pipe(t_tree **root);
int				tree_add_case(char *arg, int i, t_ndtype type, t_parse parse);
//get_stts_utils.c
char			*get_stts(char *str, int i, char *val);
//var_utils.c
bool			is_var(char c);
char			*add_var(char *str, char *var, int start, int end);
char			*find_var(char *var, char **env);
char			*get_var(char *str, int *i, char **env);
//pipe_utils.c
void			check_pipes(char *arg);
void			pipe_add2pos(t_pipe **pipes, int pos, int num);
char			**pipe_split(t_pipe *pipes, char *arg);
void			free_pipes(t_pipe **pipes);
//signs_utils.c
int				find_eq_sign(char *str);
char			*parse_signs(char *str, char **env);
int				is_diff_sign(char *sign, char c);
//quotes_utils.c
int				quotes_skip(char *str, int i);
int				get_quote_num(char *str);
char			*quotes_rm(char *str);
//tilde_utils.c
char			*parse_tilde(char *arg, char **env);

/*					EXECUTOR					*/
//executor.c
void			proc_exec_tree(t_tree **root, char ***env);
//executor_handy.c
void			holy_pid_initializer(int *cmdpid, int *proc_stts);
void			pc_utils(t_cmd *cmd, t_tree *node, char *path, char **cmds);
//cmd_utils.c
char			*get_cmd(t_tree *node, int pos);
char			**get_cmd_args(t_tree *node, int pos);
int				get_cmd_num(t_tree *node);
int				get_cmd_arg_num(t_tree *node, int pos);
//path_utils.c
char			*get_cmd_path(char *cmd, char **env);
//sig_utils.c
void			sig_handle(void);
//redir_utils.c
int				get_redir_num(t_tree *node, int pos, t_io io);
void			redir(t_tree *node, t_cmd *cmd, int *fd);
//redir_in_utils.c
void			redir_in(t_tree *node, t_cmd *cmd, int in_num);
//redir_out_utils.c
void			redir_out(t_tree *node, t_cmd *cmd, int out_num);
int				redir_hdoc(t_tree **root, t_cmd *cmd);
//redir_builtins.c
int				redir_builtin_in(t_tree *node);
int				redir_builtin_out(t_tree *node);
//heredoc_utils.c
int				handle_hdoc(t_tree **root, t_cmd *cmd);
//reset_the_term.c
void			reset_the_terminal(void);

/*				   BUILTINS					*/
//buitin_utils.c
int				print_builtin_err(char *arg);
int				run_builtin(t_tree *node, char ***env, char *cmd, int fd);
int				builtin_ret(t_tree *node, char ***env, char *cmd, int pos);
bool			is_builtin(t_tree *node, char ***env, char *cmd);
//ft_pwd.c
int				ft_pwd(int fd);
//ft_exit.c
int				ft_exit(char **args);
//ft_echo.c
int				ft_echo(char **args, int fd);
//ft_env.c
int				ft_env(char **env, int fd);
//ft_export.c
int				ft_export(char **args, char ***env, int fd);
//export_utils.c
void			export_arg_new(char *arg, char ***env, int i);
int				export_fail(char *arg);
//ft_unset.c
int				ft_unset(char **args, char ***env);
//ft_cd.c
int				ft_cd(char **args, char ***env);
//ft_cd_utils.c
int				ft_cd_checker(char **args, char ***env, char *path);

/*					 EXTRA						*/
//print_utils.c
void			print_mtx(char **mtx);
void			print_err(char *msg, int stts);
void			print_shell_err(char *cmd, char *msg, int stts);
void			print_hdoc_warn(char *eof, char *in, int stts);
void			print_syntax_error(void);
//free_utils.c
void			free_mtx(char **mtx);
void			free_tree(t_tree **node);
t_tree			**get_tree_root(t_tree **node);
int				mtx_len(char **mtx);
void			fd_close_cmd(t_tree **node);
void			fd_close_hdoc(t_tree **node);

/*					  MISC						*/
char			**get_path(char **env);
void			signal_here(void);
int				*is_inside(void);
struct termios	*term(void);
int				*num_cmds(void);
void			fd_close_all(int fd);

#endif
