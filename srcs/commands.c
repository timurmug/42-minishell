/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:20 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/04 12:47:35 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_path(char *path, char **cmd)
{
	char	*full_path;
	char	*cmd_name;
	int		fd;

	if (!(cmd_name = ft_strjoin("/", cmd[0])))
		return (NULL);
	if (!(full_path = ft_strjoin(path, cmd_name)))
	{
		free (cmd_name);
		return (NULL);
	}
	if ((fd = open(full_path, O_RDONLY)) != -1)
	{
		close(fd);
		free(cmd_name);
		return (full_path);
	}
	free(full_path);
	free(cmd_name);
	return (NULL);
}

char	*parse_path(char **cmd, t_list *env)
{
	t_list	*tmp;
	char	**splitted_path;
	int		i;
	char	*true_path;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(((t_env*)tmp->content)->name, "PATH"))
		{
			splitted_path = ft_split(((t_env*)tmp->content)->value, ':');
			i = 0;
			while (splitted_path[i])
			{
				if ((true_path = check_path(splitted_path[i++], cmd)))
				{
					ft_free_strstr(splitted_path);
					return (true_path);
				}
			}
			ft_free_strstr(splitted_path);
			break ;
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	run_command(char *line, char **cmd, t_list *env)
{
	int		pid;
	char	*true_path;

	errno = 0;
	if (!ft_strcmp("exit", cmd[0]))
		my_exit(line, cmd, env);
	if (!(true_path = parse_path(cmd, env)))
	{
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		ft_putendl_fd(cmd[0], STDERR_FILENO);
	}
	pid = fork();
	if (pid == -1)
		my_exit(line, cmd, env); // с каким значением?
	if (pid == 0)
	{
		if (execve(true_path, cmd, NULL) == -1)
			my_exit(line, cmd, env); // с каким значением?
	}
	else
	{
		free(true_path);
		wait(NULL);
	}
}
