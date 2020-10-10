/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:05:33 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/10 12:04:44 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_line(char *line, int start, int len, t_list *env)
{
	char	*buff;
	char	*s;

	if (line[start + 1] && line[start + 1] == '?')
	{
		if (!(s = ft_itoa(g_question)))
			ft_malloc_error();
		return (s);
	}
	if (!(buff = ft_substr(line, start, len)))
		ft_malloc_error();
	if ((s = find_env(&buff[1], env)))
	{
		if	(!(s = ft_strdup(s)))
			ft_malloc_error();
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
	if (line[i] == '&')
		i++;
	if (line[i] == '|' || line[i] == '&' || line[i] == '\\' ||
		(line[i - 1] == '$' && (line[i] == '?' || line[i] == '$')))
		{
			if (!(s = ft_substr(line, i + 1, len)))
				ft_malloc_error();
		}
	else
	{
		if (!(s = ft_substr(line, i, len)))
			ft_malloc_error();
	}
	if (!(buff = trim_line(line, j, i - j, env)))
	{
		if (!(buff = ft_strdup("\0")))
			ft_malloc_error();
	}
	if (!(res = ft_strjoin(buff, s)))
		ft_malloc_error();
	free(s);
	free(buff);
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
	if (!(s = ft_strdup(line)))
		ft_malloc_error();
	while (s[++i])
	{
		if (s[i] == '$' && f == 1)
		{
			if(!(tmp = ft_substr(s, 0, i)))
				ft_malloc_error();
			buff = search_env(s, i, env);
			free(s);
			if (!(s = ft_strjoin(tmp, buff)))
				ft_malloc_error();
			free(tmp);
			free(buff);
			i = -1;
		}
		else if (s[i] == '$')
		{
			buff = search_env(s, i, env);
			free(s);
			if (!(s = ft_strdup(buff)))
				ft_malloc_error();
			free(buff);
			i = -1;
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
			if (!(s = ft_strtrim(line[i], buff)))
				ft_malloc_error();
			if ((str = change_env(buff, env)))
			{
				free(line[i]);
				if (!(line[i] = ft_strjoin(str, s)))
					ft_malloc_error();
				free(s);
				free(str);
			}
			if ((line[f + 1]) && (line[i][0] == '\0'))
			{
				free(line[i]);
				if (!(line[i--] = ft_strdup(line[f + 1])))
					ft_malloc_error();
			}
		}
	}
	return (line);
}
