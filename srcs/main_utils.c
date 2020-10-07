/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:46 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/07 11:53:47 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			write_prompt(void)
{
	char	*path;

	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd("minishell:~", STDOUT_FILENO);
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	free(path);
}

int				is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == ';' || c == '\'' \
	|| c == '\"')
		return (1);
	return (0);
}

static char 	*find_env(char *line, t_list *env)
{
	t_list	*tmp;
	char	*s;

	tmp = env;
	while (tmp)
	{
		if ((t_env*)tmp->content && !ft_strcmp(((t_env*)tmp->content)->name, line))
			return ((s = ((t_env*)tmp->content)->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void			replase_env(char **cmd, t_list *env)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
		{
			if ((s = find_env(&cmd[i][1], env)))
			{
				free(cmd[i]);
				cmd[i] = ft_strdup(s);
				break ;
			}
			else if (cmd[i + 1] && !(s = find_env(&cmd[i][1], env)))
			{
				free(cmd[i]);
				cmd[i] = ft_strdup(cmd[i + 1]);
				i++;
				while (cmd[i])
				{
					free(cmd[i]);
					cmd[i++] = ft_strdup("\0");
				}
				i--;
			}
		}
		i++;
	}
}

int					print_dir(char **cmd)
{
	if (cmd[0][0] == '/' && cmd[0][1] != 'p')
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putendl_fd(IS_A_DIR, STDERR_FILENO);
		return (1);
	}
	else if (cmd[0][0] == '/' && cmd[0][1] == 'p')
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putendl_fd(P_DEN, STDERR_FILENO);
		return (1);
	}
	return (0);
}
