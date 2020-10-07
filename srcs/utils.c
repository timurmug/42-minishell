/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:05:33 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/07 15:02:29 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_cmd(char **line, t_list *env)
{
	char *buff1;
	char *buff2;
	char *s;
	int i;
	int j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (ft_strchr(line[i], '=') && ft_strchr(line[i], '$'))
		{
			while (line[i][j] && line[i][j] != '$')
				j++;
			buff1 = ft_substr(line[i], 0, j);
			buff2 = ft_substr(line[i], j, ft_strlen(line[i]));
			if ((s = find_env(&buff2[1], env)))
			{
				free(buff2);
				buff2 = ft_strdup(s);
			}
			else
			{
				free(buff2);
				buff2 = ft_strdup("\0");
			}
			free(line[i]);
			line[i] = ft_strjoin(buff1, buff2);
			free(buff1);
			free(buff2);
		}
		i++;
	}
	return (line);
}
