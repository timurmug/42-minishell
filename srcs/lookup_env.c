/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:33:52 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/12 09:40:36 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 			*find_env(char *line, t_list *env)
{
	t_list	*tmp;
	char	*s;

	tmp = env;
	while (tmp)
	{
		if ((t_env*)tmp->content && !ft_strcmp(((t_env*)tmp->content)->name, line))
		{
			s = ((t_env*)tmp->content)->value;
			return (s);
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*lookup_env(char **line, t_list *env)
{
	int		i;
	char	*res;
	char	*buff;
	char	t;

	(*line)++;
	buff = (*line);
	i = 0;
	while (buff[i] && !ft_strchr(" $<>|;\'\"\\", buff[i])
			&& !ft_issymbol(buff[i])) //is_symbol think about it
		i++;
	t = buff[i];
	buff[i] = 0;
	if (buff[0] == '?' || (i == 0 && t == '?'))
	{
		if (!(res = ft_itoa(g_question)))
			ft_malloc_error();
		*line = &buff[i]; 
		return (res);
	}
	else if (i == 0)
	{
		if (!(res = ft_strdup("$")))
			ft_malloc_error();
	}
	else
	{
		if (!(res = ft_strdup(find_env(buff, env))))
			ft_malloc_error();
	}
	buff[i] = t;
	*line = &buff[i]; 
	return (res);
}