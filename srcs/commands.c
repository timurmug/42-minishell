/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:20 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 18:28:47 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bash_command(char *true_path, char **cmd,
								t_list **env, int is_path)
{
	int pid;

	pid = fork();
	if (pid == -1)
		ft_error_errno_exit();
	if (pid == 0)
	{
		if (execve(true_path, cmd, env_to_strstr(*env)) == -1)
			ft_error_errno_exit();
	}
	else
	{
		if (!is_path)
			free(true_path);
		wait(NULL);
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
	else if ((is_path = is_it_path(cmd, &true_path)))
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
		dup2(fd_pipe->stdout_write, STDOUT_FILENO);
		run_command(line, cmd, env);
		close(fd_pipe->stdin_read);
		close(STDOUT_FILENO);
		exit(0);
	}
	else
	{
		dup2(fd_pipe->stdin_read, STDIN_FILENO);
		close(fd_pipe->stdout_write);
		wait(NULL);
		close(fd_pipe->stdin_read);
	}
}
