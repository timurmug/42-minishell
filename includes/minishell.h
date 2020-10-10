/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:05:00 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/10 11:33:58 by qtamaril         ###   ########.fr       */
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

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

typedef struct	s_fd
{
	// int			pid;
	int			stdin_read;
	int			stdout_write;

}				t_fd;

int				check_variable(char **cmd, char *param, int i);
int				check_builtins(char *line, char **cmd, t_list **env);
int				my_cd(char **cmd, t_list **env);
int				my_echo(char **cmd, t_list *env, char *strlowcase);
int				my_env(t_list *env, char *strlowcase);
void			print_export(t_list *env);
int				check_export(char **cmd, t_list **env);
int				my_pwd(char *strlowcase);
int				check_unset(char **cmd, t_list **env);

void 			get_pipe(t_fd *fd_pipe, char **line);
void			run_command(char *line, char **cmd, t_list **env);

void			my_exit(char *line, char **cmd, t_list *env);

void			write_prompt(void);
int				is_separator(char c);

void			env_sort(t_list **begin_list);
int				add_env(t_list **lst, char *name, char *value);
int				init_env(t_list **lst, char **env);
void			free_env(t_list *lst);

char			**ft_env(char **line, t_list *env);
char 			*find_env(char *line, t_list *env);
int				print_dir(char **cmd);

void			ft_malloc_error();

int				g_question;

#endif
