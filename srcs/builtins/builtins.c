/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:33:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/11 15:07:27 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		variable_error(char **cmd, int i)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(cmd[0], STDERR_FILENO);
	ft_putstr_fd(": \'", STDERR_FILENO);
	ft_putstr_fd(cmd[i], STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
	return (0);
}

int		check_variable(char **cmd, char *param, int i)
{
	int j;

	if (ft_strstrlen(cmd) == 1)
		return (0);
	if (!ft_isalpha(param[0]) && param[0] != '_')
		return (variable_error(cmd, i));
	j = 0;
	while (param[j])
	{
		if (!ft_isalnum(param[j]) && param[j] != '_')
			return (variable_error(cmd, i));
		j++;
	}
	return (1);
}

int		check_builtins2(char **cmd, t_list **env)
{
	char	*strlowcase;

	strlowcase = ft_strlowcase(ft_strdup(cmd[0]));
	if (!ft_strcmp(strlowcase, "echo"))
		return (my_echo(cmd, *env, strlowcase)); //не всегда работает корретно
	else if (!ft_strcmp(strlowcase, "pwd"))
		return (my_pwd(strlowcase));
	else if (!ft_strcmp(strlowcase, "env"))
		return (my_env(*env, strlowcase));
	else if (!ft_strcmp(strlowcase, "cd"))
	{
		free(strlowcase);
		return (1);
	}
	free(strlowcase);
	return (0);
}

int		check_builtins(char *line, char **cmd, t_list **env)
{

	if (!ft_strcmp(cmd[0], "export"))
		return (check_export(cmd, env));
	else if (!ft_strcmp(cmd[0], "unset"))
		return (check_unset(cmd, env));
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		my_exit(line, cmd, *env);
	}
	else if (!ft_strcmp(cmd[0], "cd")) //cd переменная не работает
		return (my_cd(cmd, env));
	return check_builtins2(cmd, env);
}
