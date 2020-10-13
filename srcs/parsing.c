/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:02:30 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 09:59:17 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static	void	ft_str_utils(char *str_var, char **line,
								char **temp, int *index)
{
	if (str_var)
	{
		(*index) += ft_strlen(str_var);
		if (!((*temp) = ft_strjoin_gnl((*temp), str_var)))
			ft_malloc_error();
		free(str_var);
	}
	else
	{
		(*temp) = ft_str_realloc((*temp), 1);
		(*temp)[(*index)++] = **line;
		(*line)++;
	}
}

char			*get_str_double_quotes(char **line, t_list *env)
{
	char	*temp;
	int		index;
	char	*str_var;

	index = 0;
	temp = NULL;
	(*line)++;
	while (**line && **line != '\"')
	{
		g_flag = 1;
		str_var = NULL;
		if (**line == '\\' && (*(*line + 1) == '$' || \
		*(*line + 1) == '\\' || *(*line + 1) == '\"'))
			(*line)++;
		if (**line == '$')
			str_var = lookup_env(line, env);
		ft_str_utils(str_var, line, &temp, &index);
	}
	if (**line == '\"')
		(*line)++;
	if (!g_flag)
		temp = ft_strdup("");
	return (temp);
}

char			*get_str_single_quotes(char **line)
{
	char	*temp;
	int		index;

	index = 0;
	temp = NULL;
	(*line)++;
	while (**line && **line != '\'')
	{
		g_flag = 1;
		// if (**line == '\\' && *(*line + 1) == '\\')
		// 	(*line)++;
		temp = ft_str_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	if (**line == '\'')
		(*line)++;
	if (!g_flag)
		temp = ft_strdup("");
	return (temp);
}

char			*get_str_regular(char **line, t_list *env)
{
	char	*temp;
	int		index;
	char	*str_var;

	index = 0;
	temp = NULL;
	g_flag = 1;
	while (**line && !ft_strchr(" \t<>|;\'\"", **line))
	{
		str_var = NULL;
		if (**line == '\\')
			(*line)++;
		else if (**line == '$')
		{
			g_flag = 1;
			str_var = lookup_env(line, env);
		}
		ft_str_utils(str_var, line, &temp, &index);
	}
	return (temp);
}

char			*parse_argument(char **line, t_list *env)
{
	char	*temp;
	char	*res;

	res = NULL;
	g_flag = 0;
	while (**line && !ft_strchr("|><;", **line))
	{
		temp = NULL;
		if (ft_isspace(**line))
			break ;
		if (**line == '\"')
			temp = get_str_double_quotes(line, env);
		else if (**line == '\'')
			temp = get_str_single_quotes(line);
		else
			temp = get_str_regular(line, env);
		if (temp && !(res = ft_strjoin_gnl(res, temp)))
			ft_malloc_error();
		if (temp)
			free(temp);
	}
	return (res);
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
		while (ft_isspace(**line))
			(*line)++;
		if (!**line || (**line && **line == ';'))
		{
			if (g_pipe_flag == 2 || g_pipe_flag == 1)
				g_pipe_flag = -1;
			// close(stdin_read);
			// close(stdout_write);
			break ;
		}
		if (**line == '|')
		{
			(void)fd_pipe;

			close(stdin_read);
			close(stdout_write);
			// dup2(g_tmpin, 0);
			// dup2(g_tmpout, 1);

			printf("1. stdin_read: %d\n", stdin_read);
			printf("1. stdout_write: %d\n", stdout_write);
			printf("1. STDIN_FILENO: %d\n", STDIN_FILENO);
			printf("1. STDOUT_FILENO: %d\n\n", STDOUT_FILENO);

			int fd[2];
			if (pipe(fd) == -1)
				exit(0); // с каким значением?
			if (g_pipe_flag == -2)
				g_pipe_flag = 1;
			else if (g_pipe_flag == 1 || g_pipe_flag == 2)
				g_pipe_flag = 2;
			stdin_read = fd[0];
			stdout_write = fd[1];

			printf("2. stdin_read: %d\n", stdin_read);
			printf("2. stdout_write: %d\n", stdout_write);
			printf("2. STDIN_FILENO: %d\n", STDIN_FILENO);
			printf("2. STDOUT_FILENO: %d\n", STDOUT_FILENO);
			printf("------------------------------------------\n\n");


			// get_pipe_fd(fd_pipe, line);
			break ;
		}
		// else if (**line == '|')
		// {
		// 	ft_putendl_fd("i see pipe in the end", 1);
		// }
		if ((str = parse_argument(line, env)))
		{
			if (str[0] == '\0' && !g_flag) //&& cmd[0] && !ft_strcmp(cmd[0], "cd"))
			{
				cmd = ft_strstr_realloc(cmd, 1);
				cmd[i++] = str;
			}
			else if (str[0] != '\0')
			{
				cmd = ft_strstr_realloc(cmd, 1);
				cmd[i++] = str;
			}
			else
				free(str);
		}
	}
	if (!**line)
	{
		if (g_pipe_flag == 2 || g_pipe_flag == 1)
			g_pipe_flag = -1;
		// close(stdin_read);
		// close(stdout_write);
	}
	return (cmd);
}
