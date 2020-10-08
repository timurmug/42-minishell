/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:05:33 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/08 18:54:52 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_line(char *line, int start, int len, t_list *env)
{
	char	*buff;
	char	*s;

	buff = ft_substr(line, start, len);
	if ((s = find_env(&buff[1], env)))
	{
		free(buff);
		return(s);
	}
	free(buff);
	return (0);
}

char	*change_env(char *line, t_list *env)
{
	char	*s;
	char	*s1;
	char	*buff;
	int		i;
	int		j;

	i = -1;
	s = ft_strdup("\0");
	while (line[++i])
	{
		if (line[i] == '$')
		{
			j = i;
			i++;
			while (line[i] && line[i] != '$' && line[i] != '.')
				i++;
			if (!(buff = trim_line(line, j, i - j, env)))
				buff = "";	
			i--;
			s1 = ft_strdup(s);
			free(s);
			s = ft_strjoin(s1, buff);
			free(s1);
		}
	}
	return (s);
}

char	**ft_env(char **line, t_list *env)
{
	char	*s;
	char	*str;
	char	*buff;
	int		i;
	int		f;
	int		len;

	i = -1;
	f = -1;
	len = ft_strstrlen(line);
	while (line[++i] && ++f < len)
	{
		if ((buff = ft_strchr(line[i], '$')))
		{
			s = ft_strtrim(line[i], buff);
			if ((str = change_env(buff, env)))
			{
				free(line[i]);
				line[i] = ft_strjoin(s, str);
				free(s);
				free(str);
			}
			if ((line[f + 1]) && (line[i][0] == '\0'))
			{
				free(line[i]);
				line[i--] = ft_strdup(line[f + 1]);
			}
		}
	}
	return (line);
}
