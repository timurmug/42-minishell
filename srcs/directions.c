/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 14:35:27 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_pipe_fd(char **line, t_fd *fd_pipe)
{
	int fd[2];

	(*line)++;
	if (pipe(fd) == -1)
		ft_error_errno_exit();
	fd_pipe->stdin_read = fd[0];
	fd_pipe->stdout_write = fd[1];
	fd_pipe->pipe_flag = 1;
}

void			back_redir(char **line, t_fd *fd_pipe, t_list *env);

void			double_redir(char **line, t_fd *fd_pipe, t_list *env)
{
	char	*file_name;
	int		fd;

	(*line)++;
	if (!check_redirs(line))
		return ;
	while (ft_isspace(**line))
		(*line)++;
	if (!(file_name = parse_argument(line, env)))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline\'", 1);
		return ;
	}
	if ((fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		ft_error_errno_exit();
	free(file_name);
	if (fd_pipe->stdout_write >= 0) // хз
		fd_pipe->stdout_write = fd;
	// dup2(fd_pipe->stdout_write, 1);
}

void			forward_redir(char **line, t_fd *fd_pipe, t_list *env)
{
	char *file_name;
	int fd;

	if (!check_redirs(line))
		return ;
	while (ft_isspace(**line))
		(*line)++;
	if (!(file_name = parse_argument(line, env)))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline\'", 1);
		return ;
	}
	if ((fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error_errno_exit();
	free(file_name);
	if (fd_pipe->stdout_write >= 0)
		fd_pipe->stdout_write = fd;
		
}

// кейс 234>>12 работает неправильно
// echo 123 > test | cat
//echo 123 > test | ls
void			get_redir_fd(char **line, t_fd *fd_pipe, t_list *env)
{
	fd_pipe->stdin_read = 0;
	fd_pipe->stdout_write = 1;
	while (*line)
	{
		// get_pipe_fd(fd_pipe);
		while (ft_isspace(**line))
			(*line)++;
		if (!(ft_strncmp(*line, ">>", 2)))
		{
			get_pipe_fd(line, fd_pipe);
			// fd_pipe->was_redir = 1;
			// fd_pipe->pipe_flag = 0;
			double_redir(line, fd_pipe, env);
		}
		else if (!(ft_strncmp(*line, ">", 1)))
		{
			get_pipe_fd(line, fd_pipe);
			// fd_pipe->was_redir = 1;
			// fd_pipe->pipe_flag = 0;
			forward_redir(line, fd_pipe, env);
		}
		else if (!(ft_strncmp(*line, "<", 1)))
			;//back_redir(line, fd_pipe, env);
		else
			break ;
	}
}
