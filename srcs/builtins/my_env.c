/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:10:39 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 15:29:22 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_list *env)
{
	t_list	*tmp;
	t_env	*content;

	tmp = env;
	if (!tmp)
		return (0);
	// while (tmp && (t_env*)tmp->content)
	while (tmp)
	{
		content = (t_env*)tmp->content;
		ft_putstr_fd(content->name, STDOUT_FILENO);
		if (content->name)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(content->value, STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
	return (1);
}
