/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:05:00 by qtamaril          #+#    #+#             */
/*   Updated: 2020/09/30 15:25:31 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>

# define DEFAULT "\e[39m\e[0m"
# define GREEN "\e[92m\e[1m"

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

int				init_env(t_list **lst, char **env);
void			ft_free_strstr(char **splitted);
void			free_env(t_list *lst);



#endif
