/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:33:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 13:22:38 by qtamaril         ###   ########.fr       */
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

	if (ft_strstrlen(cmd) == 1)
		return (0);

	if (!ft_isalpha(cmd[1][0]) && cmd[1][0] != '_')
		return (variable_error(cmd));
	i = 0;
	while (cmd[1][i])
	{
		if (!ft_isalnum(cmd[1][i]) && cmd[1][i] != '_')
			return (variable_error(cmd));
		i++;
	}
	return (1);
}

int		check_builtins(char *line, char **cmd, t_list *env)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (my_echo(cmd, env)); //не всегда работает корретно
	else if (!ft_strcmp(cmd[0], "cd")) //cd переменная не работает
		return (my_cd(cmd, env));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (my_pwd());
	else if (!ft_strcmp(cmd[0], "export"))
	{
		if (check_variable(cmd))
			;
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "unset"))
	{
		if (check_variable(cmd))
			my_unset(env, cmd);
		return (1);
	}
	else if (!ft_strcmp(cmd[0], "env"))
		return (my_env(env));
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		my_exit(line, cmd, env);
	}
	return (0);
}
