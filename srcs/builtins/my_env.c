/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:10:39 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 16:19:37 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_list *env)
{
	t_env	*content;

	if (!env)
		return (0);
	while (env)
	{
		content = (t_env*)env->content;
		ft_putstr_fd(content->name, STDOUT_FILENO);
		if (content->name)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(content->value, STDOUT_FILENO);
		}
		env = env->next;
	}
	return (1);
}
