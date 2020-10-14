/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 09:35:42 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			get_pipe_fd(t_fd *fd_pipe)
{
	int fd[2];

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
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// printf("%s\n", file_name);
	free(file_name);
	if (fd_pipe->stdout_write >= 0) //хз
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
//	printf("%s\n", file_name);
	free(file_name);
	if (fd_pipe->stdout_write >= 0) //хз
		fd_pipe->stdout_write = fd;
}

void			get_redir_fd(char **line, t_fd *fd_pipe, t_list *env)
{
	char *temp_line;

	(void)env;
	fd_pipe->stdin_read = 0;
	fd_pipe->stdout_write = 1;
	temp_line = *(line);
	while (*temp_line)
	{
		//подменить fd
		while (ft_isspace(*temp_line))
			temp_line++;
		if (!(ft_strncmp(temp_line, ">>", 2)))
			double_redir(&temp_line, fd_pipe, env);
		else if (!(ft_strncmp(temp_line, ">", 1)))
			forward_redir(&temp_line, fd_pipe, env);
		else if (!(ft_strncmp(temp_line, "<", 1)))
			;//back_redir(&temp_line, fd_pipe, env);
		else
			break ;
	}
	*(line) = temp_line;
}
