/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:05:00 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 13:19:03 by qtamaril         ###   ########.fr       */
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
# define SHELL "minishell: "

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

int				check_builtins(char *line, char **cmd, t_list *env);
int				my_cd(char **cmd, t_list *env);
int				my_echo(char **cmd, t_list *env);
int				my_env(t_list *env);
int				my_pwd(void);
void			my_unset(t_list *env, char **vars);
// void			my_unset(t_list *env);
// void			my_unset(t_list *env, char *variable);

void			run_command(char *line, char **cmd, t_list *env);

void			my_exit(char *line, char **cmd, t_list *env);

void			write_prompt(void);
int				is_separator(char c);
void			print_env_list(t_list	*env); //delete me

int				init_env(t_list **lst, char **env);
void			free_env(t_list *lst);


#endif
