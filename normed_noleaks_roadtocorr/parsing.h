/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 12:33:23 by rvalton           #+#    #+#             */
/*   Updated: 2022/01/05 17:27:54 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/select.h>
# include <sys/wait.h>

# define S_QUOTE 39
# define D_QUOTE 34

extern unsigned int			g_exit_status;

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_heredoc	t_heredoc;
typedef struct s_pipe		t_pipe;
typedef struct s_exec		t_exec;

struct	s_env
{
	char				*name;
	char				*value;
	t_env				*nxt;
};

struct	s_cmd
{
	t_heredoc			*heredoc;
	char				**argv;
	int					*redir;
	t_cmd				*nxt;
};

struct	s_heredoc
{
	char				*line;
	t_heredoc			*nxt;
};

struct	s_pipe
{
	t_cmd				*tmp;
	pid_t				pid;
	int					fd[2];
	int					oldfd;
	int					status;
	int					i;
};

struct	s_exec
{
	pid_t				pid;
	int					fd[2];
	int					status;
};

void		ft_free_execve(t_env **env, t_cmd **cmd, char ***argv);
void		ft_memset(void *s, int c, size_t n);

void		ft_main_handler(int signum);
void		ft_fork_handler(int signum);
void		ft_pipe_handler(int signum);
void		ft_set_sigaction(struct sigaction *action, char which);

int			ft_is_alpha(char c);
int			ft_is_digit(char c);
int			ft_is_redir(char c);

char		*ft_itoa(int nb);
int			ft_atoi(const char *nptr);

char		**ft_split(char **path, char c);
char		**ft_get_execve_argv(char **argv);
void		ft_free_ctab(char ***ctab);

int			ft_parse_error(char *rdline);
int			ft_wrong_exit_arg(char *code);

int			ft_prompt(t_env **env);
void		ft_piping(t_env **env, t_cmd **cmd);

int			ft_execve_in_pipe(t_env **env, t_cmd **cmd, char *path);

t_env		*ft_hadd_tolist_env(t_env *list, char *name, char *value);
t_env		*ft_eadd_tolist_env(t_env *list, char *name, char *value);
t_env		*ft_ndelete_env(t_env *list, int n);
void		ft_free_list_env(t_env **list);

char		**ft_tenv_to_envp(t_env *env);
t_env		*ft_envp_to_tenv(char **env_p);

int			ft_strcomp(char *str1, char *str2);
char		*ft_get_env(t_env *env, char *name, int *env_path);

char		*ft_set_path(char *path, char *value);
int			ft_print_ex_error(char *error, char *cmd, char ***path_split,
				char *path);
char		*ft_find_valid_path(char ***path_split, char *cmd);
int			ft_execve(char **argv, t_env **env);
void		ft_hdl_arg_execve(t_env **env, t_cmd **cmd);

int			ft_open_splr(int *in, int (*fd)[2], char *file);
int			ft_open_dblr(int *out, int (*fd)[2], char *file,
				t_heredoc *heredoc);
int			ft_open_splw(int *out, int (*fd)[2], char *file);
int			ft_open_dblw(int *out, int (*fd)[2], char *file);

void		ft_close_fd(int fd[2]);
void		ft_dup2_fd(int fd[2]);
char		**ft_clean_redir(t_cmd **cmd);
int			ft_get_fd(int (*fd)[2], t_cmd **cmd);

int			ft_is_builtin(char *exe);
void		ft_exec_builtin(t_env **env, t_cmd **cmd);
void		ft_exec_builtinpipe(t_env **env, t_cmd **cmd);

int			ft_is_arg_export_valid(char *arg);
int			ft_env(t_env *env, char **argv);
int			ft_hdl_arg_unset(t_env **env, char **argv);
int			ft_unset(t_env **env, char *name);
int			ft_hdl_arg_export(t_env **env, char **argv);
int			ft_export(t_env **env, char *arg);
int			ft_pwd(void);
int			ft_get_exit_status(int status);
int			ft_exit(t_env **env, t_cmd **cmd, char *line, char **argv);
int			ft_echo(char **argv);
int			ft_hdl_arg_cd(t_env **env, char **argv);
int			ft_cd(t_env **env, char *dir);

t_cmd		*ft_hadd_tolist_cmd(t_cmd *list, char **split, int *redir);
t_cmd		*ft_eadd_tolist_cmd(t_cmd *list, char **split, int *redir,
				t_heredoc *heredoc);
void		ft_free_list_cmd(t_cmd **list);

int			ft_malloc_dblchar(char ***tmp, int size);
int			ft_malloc_splchar(char **tmp, int size);
int			ft_malloc_dblint(int ***tmp, int size);
int			ft_malloc_splint(int **tmp, int size);

char		**ft_double_realloc(char **str, char ***split);
char		*ft_realloc(char **str, char c);

int			ft_size_list_cmd(t_cmd *list);
void		ft_print_list_cmd(t_cmd *list);
int			ft_size_list_env(t_env *list);
void		ft_print_list_env(t_env *list);

void		ft_print_str(char *str);
int			ft_strlen(char *str);
char		*ft_str_copy(char **str);
char		*ft_str_copy_nofree(char *str);
int			ft_strncomp(char *str, char *comp, int n);

int			ft_is_quote(char c);
int			ft_is_quote_needed(char *arg, int i);

int			ft_is_char_quoted(char *line, int i, int j, char c);

t_heredoc	*ft_set_heredoc(t_env *env, char **cmd_char, int *red_tab);
int			ft_heredoc(t_env *env, t_heredoc **heredoc, char *eof, int quoted);

t_heredoc	*ft_eadd_tolist_heredoc(t_heredoc *list, char *line);
void		ft_free_list_heredoc(t_heredoc *list);
void		ft_print_list_heredoc(t_heredoc *list, int fd);

char		**ft_pipe_split(char **rdline);
char		**ft_set_redir(char **pipe_char);

char		**ft_cmdline_split(char **line);
int			*ft_set_redir_tab(char **cmd_char);

char		*ft_clean_str(char *str);
char		**ft_clean_cmdchar(char **cmd_char);

int			ft_is_dollar(char *line, int i);
char		*ft_get_dollar_value(t_env *env, char *str, int i);
int			ft_size_dollar(t_env *env, char *str, int i);

char		*ft_interpret_dollar(t_env *env, char *str);
char		**ft_dollar_parse(t_env *env, char **cmd_char);

#endif
