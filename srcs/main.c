/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 09:56:10 by qtamaril         ###   ########.fr       */
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
				printf("--------g_pipe_flag-------: %d\n", g_pipe_flag);

				run_command(line, cmd, env);
				// my_fork(line, cmd, env);
				ft_free_strstr(cmd);
			}
		}
	}
}

int		main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;
	// int		tmpin;
	// int		tmpout;

	(void)ac;
	(void)av;
	env = NULL;
	g_question = 0;
	g_tmpin = dup(0);
	g_tmpout = dup(1);
	ft_lstadd_back(&env, ft_lstnew(NULL));
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		dup2(g_tmpin, STDIN_FILENO);
		dup2(g_tmpout, STDOUT_FILENO);
		write_prompt();
		g_pipe_flag = -2;
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
