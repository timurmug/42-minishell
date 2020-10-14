/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/10/14 11:31:28 by fkathryn         ###   ########.fr       */
=======
/*   Updated: 2020/10/14 13:35:06 by qtamaril         ###   ########.fr       */
>>>>>>> f038781dabc29773646885991d5c1f9763d27dec
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
void	run_command_or_fork(char *line, t_fd *fd_pipe, t_list **env, char **cmd)
=======
int		compile_cmd(char *line, t_fd *fd_pipe, t_list **env, char **cmd)
>>>>>>> f038781dabc29773646885991d5c1f9763d27dec
{
	if (g_redir_error == 1)
	{
		if (cmd)
			ft_free_strstr(cmd);
		return (0);
	}
	if (cmd)
	{
		if (fd_pipe->pipe_flag == 1)
			my_fork(line, cmd, env, fd_pipe);
		else
			run_command(line, cmd, env);
		ft_free_strstr(cmd);
		return (1);
	}
	return (1);
}

void	minishell(char *line, t_list **env)
{
	char	**cmd;
	t_fd	fd_pipe;

	if (!check_dir_in_begin(&line))
		return ;
	// fd_pipe.was_redir = 0;
	while (*line)
	{
		if (*line == ';')
		{
			// fd_pipe.was_redir = 0;
			dup2(4, 0);
			dup2(3, 1);
			line++;
		}
		else
		{
			cmd = parse_line(&line, &fd_pipe, *env);
<<<<<<< HEAD
			run_command_or_fork(line, &fd_pipe, env, cmd);
=======
			if (!compile_cmd(line, &fd_pipe, env, cmd))
				return ;
>>>>>>> f038781dabc29773646885991d5c1f9763d27dec
		}
	}
}

// контр с завершает процеесс/ выдает новый промт и %? = 1
// контр d должен завершить минишел
// bash-3.2$ cat
// ^\Quit: 3
//  echo(стекд + \)echo 123 выполняет echo 123
int		main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;

	(void)ac;
	(void)av;
	env = NULL;
	g_question = 0;
	dup2(STDOUT_FILENO, 3);
	dup2(STDIN_FILENO, 4);
	ft_lstadd_back(&env, ft_lstnew(NULL));
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		dup2(4, STDIN_FILENO);
		write_prompt();
		g_redir_error = 0;
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
