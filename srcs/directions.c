/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:31:56 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/09 14:35:34 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_pipe(t_fd *fd_pipe, char **line)
{
	int fd[2];

	if (pipe(fd) == -1)
		exit(0); // с каким значением?
	close(fd[1]);
	fd_pipe->stdin_read = fd[0];
	dup2(fd_pipe->stdin_read, STDIN_FILENO);
	(*line)++;
}
