/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 11:33:52 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/10 11:53:37 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lookup_env(char **line, t_list *env)
{
	int		len;
	int		i;
	char	*buff;

	len = 1;
	i = 0;
	while (line[len] && !ft_strchr(" <>|;\'\"", line[len]))
		len++;
	while (i < len)
	{
		if ((buff = ft_strchr(line[i], '$')))
		{
		}
	}
	return (line);
}