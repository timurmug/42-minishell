/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:05:00 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 15:49:15 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>

# define DEFAULT "\e[39m\e[0m"
# define GREEN "\e[92m\e[1m"
# define CLEAN "\e[1;1H\e[2J"
# define CMD_NOT_FOUND ": command not found"
# define IS_A_DIR ": is a directory"
# define P_DEN ": Permission denied"
# define SHELL "minishell: "
# define NO_FILE_DIR ": No such file or directory"

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

typedef struct	s_fd
{
	int			pipe_flag;
	int			was_redir;
	int			stdin_read;
	int			stdout_write;
}				t_fd;

int				check_variable(char **cmd, char *param, int i);
int				check_builtins(char *line, char **cmd, t_list **env);
int				my_cd(char **cmd, t_list **env);
int				my_echo(char **cmd, char *strlowcase);
int				my_env(t_list *env, char *strlowcase);
void			print_export(t_list *env);
int				check_export(char **cmd, t_list **env);
int				my_pwd(char *strlowcase);
int				check_unset(char **cmd, t_list **env);
void			my_exit(char *line, char **cmd, t_list *env);

void			run_command(char *line, char **cmd, t_list **env);
void			my_fork(char *line, char **cmd, t_list **env, t_fd *fd_pipe);

void			get_pipe_fd(char **line, t_fd *fd_pipe);
void			get_redir_fd(char **line, t_fd *fd_pipe, t_list *env);

void			env_sort(t_list **begin_list);
int				add_env(t_list **lst, char *name, char *value);
int				init_env(t_list **lst, char **env);
void			free_env(t_list *lst);
char			**env_to_strstr(t_list *env);

char			*lookup_env(char **line, t_list *env);

void			ft_error_errno_exit(void);
void			error_from_errno(char *param);
void			error_is_a_dir(char *param);
void			error_perm_denied(char *param);
void			error_no_file_or_dir(char *param);
void			error_cmd_not_found(char *param);

char			**parse_line(char **line, t_fd *fd_pipe, t_list *env);

char			*parse_argument(char **line, t_list *env);

int				is_it_path(char **cmd, char **true_path);
char			*parse_path(char **cmd, t_list *env);
char			*check_path(char *path, char **cmd);

void			write_prompt(void);
int				check_dir_in_begin(char **line);
int				check_redirs(char **line);

int				g_status;
int				g_flag;
int				g_redir_error;

#endif
