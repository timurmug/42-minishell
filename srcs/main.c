/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 15:11:25 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//bash-3.2$ >>12 -
//bash-3.2$ >> 12
//bash-3.2$ >> 24
int		check_dir_in_begin(char **line)
{
	int	len;

	while (ft_isspace(**line))
		(*line)++;
	len = ft_strlen(*line);
	if (**line == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 1);
		return (0);
	}
	else if (**line == '>')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>'", 1);
		return (0);
	}
	return (1);
}

void	minishell(char *line, t_list **env)
{
	char	**cmd;
	t_fd	fd_pipe;

	if (!check_dir_in_begin(&line))
		return ;
	while (*line)
	{
		if (*line == ';')
		{
			dup2(4, 0);
			dup2(3, 1);
			line++;
		}
		else if (*line == '|')
			line++;
		else
		{
			cmd = parse_line(&line, &fd_pipe, *env);
			if (cmd)
			{
				if (fd_pipe.pipe_flag == 1)
					my_fork(line, cmd, env, &fd_pipe);
				else
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

	(void)ac;
	(void)av;
	env = NULL;
	g_question = 0;
	dup2(1, 3);
	dup2(0, 4);
	ft_lstadd_back(&env, ft_lstnew(NULL));
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		dup2(4, 0);
		write_prompt();
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
