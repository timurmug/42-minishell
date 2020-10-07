/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:30:08 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/07 16:54:03 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*strjoin;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!(strjoin = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (s1[j])
		strjoin[i++] = s1[j++];
	j = 0;
	while (s2[j])
		strjoin[i++] = s2[j++];
	strjoin[i] = '\0';
	return (strjoin);
}
