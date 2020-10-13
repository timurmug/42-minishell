/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 20:17:17 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pipe_fd(t_fd *fd_pipe)
{
	int fd[2];

	if (pipe(fd) == -1)
		ft_error_errno_exit();
	fd_pipe->stdin_read = fd[0];
	fd_pipe->stdout_write = fd[1];
	fd_pipe->pipe_flag = 1;
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
		while (ft_isspace(*temp_line))
			temp_line++;
		if (!(ft_strncmp(temp_line, ">>", 2)))
			;//double_redir(&temp_line, );
		else if (!(ft_strncmp(temp_line, ">", 1)))
			;//forward_redir(&temp_line, );
		else if (!(ft_strncmp(temp_line, "<", 1)))
			;//back_redir(&temp_line, );
		else
			break ;
	}
	*(line) = temp_line;
}