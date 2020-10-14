/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:20 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 17:58:25 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bash_command(char *true_path, char **cmd,
								t_list **env, int is_path)
{
	int pid;
	int status;

	errno = 0;
	g_status = 0;
	pid = fork();
	if (pid == -1)
		ft_error_errno_exit();
	if (pid == 0)
	{
		if (execve(true_path, cmd, env_to_strstr(*env)) == -1)
			ft_error_errno_exit();
		exit(0); // хз сколько
	}
	else
	{
		if (!is_path)
			free(true_path);
		wait(&status);
		if (WIFEXITED(status))
			g_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_status = WTERMSIG(status) + 128;
	}
}

void	run_command(char *line, char **cmd, t_list **env)
{
	char	*true_path;
	int		is_path;

	errno = 0;
	is_path = 0;
	if (check_builtins(line, cmd, env))
		return ;
	else if ((is_path = is_it_path(cmd, &true_path)) < 0)
		return ;
	else if (is_path == 1)
		;
	else if (!(true_path = parse_path(cmd, *env)))
	{
		error_cmd_not_found(cmd[0]);
		return ;
	}
	exec_bash_command(true_path, cmd, env, is_path);
}

void	my_fork(char *line, char **cmd, t_list **env, t_fd *fd_pipe)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error_errno_exit();
	if (pid == 0)
	{
		if (fd_pipe->was_redir)
		{
			close(fd_pipe->stdin_read);
			// fd_pipe->was_redir = 0;
		}
		dup2(fd_pipe->stdout_write, STDOUT_FILENO);
		run_command(line, cmd, env);
		close(fd_pipe->stdin_read);
		close(fd_pipe->stdout_write);
		close(STDOUT_FILENO);
		exit(0); // хз сколько
	}
	else
	{
		dup2(fd_pipe->stdin_read, STDIN_FILENO);
		close(fd_pipe->stdout_write);
		wait(NULL);
		close(fd_pipe->stdin_read);
	}
}
