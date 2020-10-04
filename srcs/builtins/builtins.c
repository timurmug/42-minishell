/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:33:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/04 16:50:45 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		variable_error(char **cmd)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": \'", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
	return (0);
}

int		check_variable(char **cmd)
{
	int i;

	if (!ft_isalpha(cmd[1][0]))
		return (variable_error(cmd));
	i = 0;
	while (cmd[1][i])
	{
		if (!(ft_isalnum(cmd[1][i])) || cmd[1][i] == '_')
			return (variable_error(cmd));
		i++;
	}
	return (1);
}

int		check_builtins(char *line, char **cmd, t_list *env)
{
	if (!ft_strcmp(cmd[0], "echo"))
	{
		my_echo(cmd, env); //не всегда работает корретно
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "cd"))
	{
		my_cd(cmd, env);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "pwd"))
	{
		my_pwd();
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "export"))
	{
		if (check_variable(cmd))
			;
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		if (check_variable(cmd))
			my_unset(env);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "env"))
	{
		my_env(env);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		my_exit(line, cmd, env);
	}
	return (0);
}
