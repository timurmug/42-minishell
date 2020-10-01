/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:05:00 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/01 16:05:56 by qtamaril         ###   ########.fr       */
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

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

int				init_env(t_list **lst, char **env);
void			ft_free_strstr(char **splitted);
void			free_env(t_list *lst);

#endif
