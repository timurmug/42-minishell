/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:55:49 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 16:34:30 by qtamaril         ###   ########.fr       */
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

char	**parse_line(char **line)
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

	(void)env;
	while (*line)
	{
		if (*line == ';')
			(*line)++;
		else
		{
			cmd = parse_line(&line);
			if (cmd)
			{
				// ft_putstrstr_fd(cmd, STDOUT_FILENO);
				run_command(line, cmd, env);
				ft_free_strstr(cmd);
//				ft_putendl_fd("--------", STDOUT_FILENO);
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
	// (void)ev;
	env = NULL;
	if (!init_env(&env, ev))
		return (0);
	// env = NULL;
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
