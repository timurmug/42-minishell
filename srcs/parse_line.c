/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:02:30 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/14 12:36:29 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	ft_add_cmd(char *str, int *i, char ***cmd)
{
	if (str[0] == '\0' && !g_flag)
	{
		(*cmd) = ft_strstr_realloc((*cmd), 1);
		(*cmd)[(*i)++] = str;
	}
	else if (str[0] != '\0')
	{
		(*cmd) = ft_strstr_realloc((*cmd), 1);
		(*cmd)[(*i)++] = str;
	}
	else
		free(str);
}

int				find_pipe_or_redir(char **line, t_fd *fd_pipe, t_list *env)
{
	if (**line == '|')
	{
		get_pipe_fd(fd_pipe);
		return (1);
	}
	else if (**line == '>')
	{
		get_redir_fd(line, fd_pipe, env);
		return (1);
	}
	else if (**line == '<')
	{
		get_redir_fd(line, fd_pipe, env);
		return (1);
	}
	return (0);
}

char			**parse_line(char **line, t_fd *fd_pipe, t_list *env)
{
	char	*str;
	char	**cmd;
	int		i;

	cmd = NULL;
	str = NULL;
	i = 0;
	while (**line)
	{
		fd_pipe->pipe_flag = 0;
		while (ft_isspace(**line))
			(*line)++;
		if (!**line || (**line && **line == ';'))
			break ;
		else if ((find_pipe_or_redir(line, fd_pipe, env)))
			break ;
		else if (g_redir_error == 1)
			break ;
		if ((str = parse_argument(line, env)))
			ft_add_cmd(str, &i, &cmd);
	}
	return (cmd);
}
