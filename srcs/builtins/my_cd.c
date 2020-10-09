/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:01:14 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/09 11:13:31 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_list *env)
{
	t_list	*tmp;
	t_env	*content;

	tmp = env;
	while (tmp)
	{
		content = (t_env*)tmp->content;
		if (content && !ft_strcmp(content->name, "HOME"))
			return (content->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd_error(char **cmd, char *home_value)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	if (!home_value)
		ft_putstr_fd(cmd[1], STDERR_FILENO);
	else
		ft_putstr_fd(home_value, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
}

void	set_pwd(t_list **env)
{
	t_list	*tmp;
	t_env	*content;
	char	*path;
	t_env	*elem;

	tmp = *env;
	path = getcwd(NULL, 0);
	while (tmp)
	{
		content = (t_env*)tmp->content;
		if (content && !ft_strcmp(content->name, "PWD"))
		{
			free(content->value);
			content->value = path;
			return ;
		}
		tmp = tmp->next;
	}
	if (!(elem = malloc(sizeof(t_env))))
		return ;
	elem->name = ft_strdup("PWD");
	elem->value = path;
	ft_lstadd_back(env, ft_lstnew(elem));
	env_sort(env);
}

void	my_cd2(char **cmd, t_list **env)
{
	if (chdir(cmd[1]) == 0)
		set_pwd(env);
	else
		cd_error(cmd, NULL);
}

int		my_cd(char **cmd, t_list **env)
{
	char	*home_value;

	if (ft_strstrlen(cmd) == 1)
	{
		if (!(home_value = find_home(*env)))
		{
			ft_putstr_fd(SHELL, STDERR_FILENO);
			ft_putstr_fd("cd: ", STDERR_FILENO);
			ft_putstr_fd("HOME", STDERR_FILENO);
			ft_putendl_fd(" not set", STDERR_FILENO);
		}
		else if (!ft_strcmp(home_value, "\0"))
		{
			set_pwd(env);
			return (1);
		}
		else if (chdir(home_value) == 0)
			set_pwd(env);
		else
			cd_error(cmd, home_value);
	}
	else
		my_cd2(cmd, env);
	return (1);
}
