/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:33:52 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/10 15:45:17 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lookup_env(char **line, t_list *env)
{
	int		len;
	int		i;
	char	*res;
	char	*buff;
	char	t;

	(*line)++;
	buff = (*line);
	len = 0;
	i = 0;
	while (buff[i] && !ft_strchr(" $<>|;\'\"\\", buff[i])
			&& !ft_issymbol(buff[i++]))
		len++;
	i = 1;
	t = buff[len];
	buff[len] = 0;
	if (len == 0)
	{
		if (!(res = ft_strdup("$")))
			ft_malloc_error();
	}
	else if (buff[i] == '?')
	{
		if (!(res = ft_itoa(g_question)))
			ft_malloc_error();
	}
	else
	{
		if (!(res = ft_strdup(find_env(buff, env))))
			ft_malloc_error();
	}
	buff[len] = t;
	*line = &buff[len];
	return (res);
}