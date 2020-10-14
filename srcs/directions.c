/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 13:41:03 by qtamaril         ###   ########.fr       */
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
	char	*file_name;
	int		fd;

	(*line) += 2;
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
	if ((fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
		ft_error_errno_exit();
	free(file_name);
	if (fd_pipe->stdout_write >= 0) //хз
		fd_pipe->stdout_write = fd;
}

// кейс 234>>12 работает неправильно
// echo 123 > test | cat
// echo 123 > test | ls
void			get_redir_fd(char **line, t_fd *fd_pipe, t_list *env)
{
	char *temp_line;

	fd_pipe->stdin_read = 0;
	fd_pipe->stdout_write = 1;
	temp_line = *(line);
	while (*temp_line)
	{
		// get_pipe_fd(fd_pipe);
		while (ft_isspace(*temp_line))
			temp_line++;
		if (!(ft_strncmp(temp_line, ">>", 2)))
		{
			get_pipe_fd(fd_pipe);
			// fd_pipe->was_redir = 1;
			// fd_pipe->pipe_flag = 0;
			double_redir(&temp_line, fd_pipe, env);
		}
		else if (!(ft_strncmp(temp_line, ">", 1)))
		{
			get_pipe_fd(fd_pipe);
			// fd_pipe->was_redir = 1;
			// fd_pipe->pipe_flag = 0;
			forward_redir(&temp_line, fd_pipe, env);
		}
		else if (!(ft_strncmp(temp_line, "<", 1)))
			;//back_redir(&temp_line, fd_pipe, env);
		else
			break ;
	}
	*(line) = temp_line;
}
