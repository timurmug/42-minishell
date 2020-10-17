/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 12:38:31 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/17 17:41:12 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exit(char *line, char **cmd, t_list *env, t_fd *fd_pipe) //надо доделать!!!!
{
	size_t	len;

	// ft_free_strstr(cmd);
	// free_env(env);
	(void)line;
	(void)env;
	(void)fd_pipe;
	len = ft_strstrlen(cmd);
	// printf("fd_pipe->needed_fork  |%d|\n", fd_pipe->needed_fork );
	// printf("fd_pipe->was_redir |%d|\n", fd_pipe->was_redir);
	// printf("fft_strstrlen |%zu|\n", len);
	// if (!fd_pipe->needed_fork || (fd_pipe->needed_fork && fd_pipe->was_redir))
	// {
		ft_putendl_fd("exit", STDOUT_FILENO);
		if (len == 1)
			exit(g_status);
		else if (len == 2)
		{
			if (ft_str_is_num(cmd[1]))
				exit(ft_atoi(cmd[1]));
			else
				error_num_arg_required(cmd[1]);
		}
		else if (len > 2)
		{
			if (ft_str_is_num(cmd[1]))
			{
				ft_putendl_fd("minishell: exit: too many arguments", STDOUT_FILENO);
				g_status = 1;
			}
			else
				error_num_arg_required(cmd[1]);
		}
	// }
	return (1);
}
