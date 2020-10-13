/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:09:24 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 18:53:49 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_echo(char **cmd, t_list *env, char *strlowcase)
{
	int i;

	(void)env;
	if (ft_strstrlen(cmd) == 1)
		ft_putendl_fd("", STDOUT_FILENO);
	else if (!ft_strcmp(cmd[1], "-n"))
	{
		i = 2;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i++], STDOUT_FILENO);
			if (cmd[i])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
	}
	else
	{
		i = 1;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i++], STDOUT_FILENO);
			if (cmd[i])
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		ft_putendl_fd("", STDOUT_FILENO);
	}
	free(strlowcase);
	return (1);
}
