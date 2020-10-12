/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/12 15:38:47 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipe_in_begin(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 1);
		return (0);
	}
	return (1);
}

void	minishell(char *line, t_list **env)
{
	char	**cmd;
	t_fd	fd_pipe;

	if (!check_pipe_in_begin(&line))
		return ;
	while (*line)
	{
		if (*line == ';')
		{
			// g_pipe_flag = -2;
			line++;
		}
		else if (*line == '|')
		{
			// ft_putendl_fd("")
			// ft_putendl_fd("i see pipe", 1);

			line++;
		}
		else
		{
			cmd = parse_line(&line, &fd_pipe, *env);
			if (cmd)
			{
				run_command(line, cmd, env);
				ft_free_strstr(cmd);
			}
		}
	}
}

int		main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;
	int		tmpin = dup(0);
	int		tmpout = dup(1);

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
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		write_prompt();
		g_pipe_flag = -2;
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
