/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 12:07:05 by fkathryn         ###   ########.fr       */
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
	char *file_name;
	int fd;

	(*line) += 2;
	while (ft_isspace(**line))
		(*line)++;
	file_name = parse_argument(line, env);
	fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0644);
	free(file_name);
	if (fd_pipe->stdout_write >= 0)
		fd_pipe->stdout_write = fd;
}

void			forward_redir(char **line, t_fd *fd_pipe, t_list *env)
{
	char *file_name;
	int fd;

	(*line)++;
	while (ft_isspace(**line))
		(*line)++;
	file_name = parse_argument(line, env);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	free(file_name);
	if (fd_pipe->stdout_write >= 0)
		fd_pipe->stdout_write = fd;
		
}

void			get_redir_fd(char **line, t_fd *fd_pipe, t_list *env)
{
	fd_pipe->stdin_read = 0;
	fd_pipe->stdout_write = 1;
	while (*line)
	{
		//подменить fd
		while (ft_isspace(**line))
			(*line)++;
		if (!(ft_strncmp(*line, ">>", 2)))
			double_redir(line, fd_pipe, env);
		else if (!(ft_strncmp(*line, ">", 1)))
			forward_redir(line, fd_pipe, env);
		else if (!(ft_strncmp(*line, "<", 1)))
			;//back_redir(&temp_line, fd_pipe, env);
		else
			break ;
	}
}
