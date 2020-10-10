/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:55:18 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/10 12:38:10 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str_double_quotes(char **line, t_list *env)
{
	char	*temp;
	int		index;

	(void)env;
	index = 0;
	temp = NULL;
	(*line)++;
	while (**line && **line != '\"')
	{
		if (**line == '\\' && (*(*line + 1) == '$' || \
		*(*line + 1) == '\\' || *(*line + 1) == '\"'))
			(*line)++;
		else if (**line == '$')
		{
			// функция алины
			ft_putendl_fd("переменная", 1);
			exit(0);
		}
		temp = ft_str_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	if (**line == '\"')
	(*line)++;
	return (temp);
}

char	*get_str_single_quotes(char **line)
{
	char	*temp;
	int		index;

	index = 0;
	temp = NULL;
	(*line)++;
	while (**line && **line != '\'')
	{
		temp = ft_str_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	if (**line == '\'')
		(*line)++;
	return (temp);
}

char	*get_str_regular(char **line, t_list *env)
{
	char	*temp;
	int		index;

	(void)env;
	index = 0;
	temp = NULL;
	while (**line && !ft_strchr(" \t<>|;\'\"", **line))
	{
		if (**line == '\\')
			(*line)++;
		else if (**line == '$')
		{
			// функция алины
			ft_putendl_fd("переменная", 1);
			exit(0);
		}
		temp = ft_str_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	return (temp);
}


char	*parse_argument(char **line, t_list *env)
{
	char	*temp;
	char	*res;

	res = NULL;
	temp  = NULL;
	while (**line && !ft_strchr("|><;", **line))
	{
		if (ft_isspace(**line))
			break ;
		if (**line == '\"')
			temp = get_str_double_quotes(line, env);
		else if (**line == '\'')
			temp = get_str_single_quotes(line);
		else
			temp = get_str_regular(line, env);
		if (!(res = ft_strjoin_gnl(res, temp)))
			exit(0); // с каким значением?
		free(temp);
	}
	return (res);
}

char	**parse_line(char **line, t_fd *fd_pipe, t_list *env)
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
			break;
		if (**line == '|' && cmd)
		{
			ft_putendl_fd("i see pipe", 1);
			get_pipe(fd_pipe, line);
			break;
		}
		if ((str = parse_argument(line, env)))
		{
			cmd = ft_strstr_realloc(cmd, 1);
			cmd[i++] = str;
		}
	}
	return (cmd);
}
