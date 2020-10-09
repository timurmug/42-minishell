/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:55:49 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/09 10:25:23 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string(char **line)
{
	char *temp = NULL;
	int index = 0;

	while (**line && !is_separator(**line))
	{
		temp = ft_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	return (temp);
}

void get_pipe(t_fd *fd_pipe, char **line)
{
	int fd[2];

	if (pipe(fd) == -1)
		exit(0); // с каким значением?
	close(fd[1]);
	fd_pipe->stdin_read = fd[0];
	dup2(fd_pipe->stdin_read, STDIN_FILENO);
	(*line)++;
}

char	**parse_line(char **line, t_fd *fd_pipe)
{
	char	*str;
	char	**cmd;
	int		i;

	cmd = NULL;
	str = NULL;
	i = 0;
	while (**line)
	{
		while (**line == ' ')
			(*line)++;
		if (!**line || (**line && **line == ';'))
			break;
		if (**line == '|' && cmd)
		{
			ft_putendl_fd("i see pipe", 1);
			get_pipe(fd_pipe, line);
			break;
		}
		if (**line && is_separator(**line))
			(*line)++;
		if ((str = get_string(line)))
		{
			cmd = ft_strstr_realloc(cmd, 1);
			cmd[i++] = str;
		}
	}
	return (cmd);
}

void	minishell(char *line, t_list **env)
{
	char	**cmd;
	t_fd	fd_pipe;

	while (*line)
	{
		if (*line == ';')
			(*line)++;
		else
		{
			cmd = parse_line(&line, &fd_pipe);
			// cmd = split_cmd(cmd, *env);
			if (cmd)
				ft_env(cmd, *env);
			if (cmd && !print_dir(cmd))
			{
				// ft_putstrstr_fd(cmd, STDOUT_FILENO);
				run_command(line, cmd, env);
				ft_free_strstr(cmd);
				// ft_putendl_fd("--------", STDOUT_FILENO);
			}
		}
	}
}

int		main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;

	(void)ac;
	(void)av;
	env = NULL;
	g_question = 0;
	ft_lstadd_back(&env, ft_lstnew(NULL));
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		write_prompt();
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
