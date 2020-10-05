/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:10:39 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 13:45:27 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_env(t_list *env)
{
	t_list	*tmp;
	t_env	*content;

	tmp = env;
	// while (tmp && (t_env*)tmp->content)
	while (tmp)
	{
		content = (t_env*)tmp->content;
		ft_putstr_fd(content->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(content->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (1);
}
