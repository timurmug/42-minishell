/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:10:07 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 15:07:27 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_export(t_list *env, char **vars, char **splitted)
{
	t_env	*curr_env;
	// int		i;
	//
	// i = 1;
	// while (vars[i])
	// {
	// ft_putendl_fd(splitted[1], 1);
	// ft_putendl_fd(splitted[2], 1);
		while (env)
		{
			curr_env = (t_env*)env->content;
			if (!ft_strcmp(curr_env->name, splitted[0]))
			{
				ft_putendl_fd("im here", 1);
				free(curr_env->value);
				// curr_env->value = ft_strdup(splitted[1]);
				curr_env->value = ft_strdup(ft_strchr(vars[1], '=') + 1);
				break ;
			}
			env = env->next;
		}
	// 	i++;
	// }
	(void)vars;
}
