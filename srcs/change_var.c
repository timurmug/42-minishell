/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:05:33 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/09 11:45:33 by fkathryn         ###   ########.fr       */
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

char	*search_env(char *line, int i, t_list *env)
{
	int		j;
	int		len;
	char 	*buff;
	char	*s;
	char	*res;

	j = i;
	len = ft_strlen(line);
	i++;
	while (line[i] && !ft_issymbol(line[i]))
		i++;
	s = ft_substr(line, i, len);
	if (!(buff = trim_line(line, j, i - j, env)))
		buff = "";
	res = ft_strjoin(buff, s);
	free(s);
	return (res);
}

char	*change_env(char *line, t_list *env)
{
	int		i;
	int		f;
	char	*buff;
	char	*s;
	char 	*tmp;

	i = -1;
	s = ft_strdup(line);
	while (s[++i])
	{
		if (s[i] == '$' && f == 1)
		{
			tmp = ft_substr(s, 0, i);
			buff = search_env(s, i, env);
			free(s);
			s = ft_strjoin(tmp, buff);
			free(tmp);
			free(buff);
		}
		if (s[i] == '$')
		{
			buff = search_env(s, i, env);
			free(s);
			s = ft_strdup(buff);
			free(buff);
			i = 0;
			f = 1;
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
