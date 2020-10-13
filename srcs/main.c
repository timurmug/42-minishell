/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 20:29:21 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	compile_cmd(char *line, t_fd *fd_pipe, t_list **env, char **cmd)
{
	(void)fd_pipe;
	if (cmd)
	{
		if (fd_pipe->pipe_flag == 1)
			my_fork(line, cmd, env, fd_pipe);
		else
			run_command(line, cmd, env);
		ft_free_strstr(cmd);
	}
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
			compile_cmd(line, &fd_pipe, env, cmd);
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
