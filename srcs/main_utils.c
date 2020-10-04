/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:46 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/04 10:45:49 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_prompt(void)
{
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
}

void print_env_list(t_list	*env) 
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		t_env *content = ((t_env*)tmp->content);
		ft_putstr_fd(content->name, STDOUT_FILENO);
		ft_putstr_fd(" = ", STDOUT_FILENO);
		ft_putendl_fd(content->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
}

int		is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == ';' || c == '\'' \
	|| c == '\"')
		return (1);
	return (0);
}
