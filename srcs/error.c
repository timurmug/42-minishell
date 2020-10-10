/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:50:28 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/09 19:52:22 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_error()
{
	ft_putstr_fd(SHELL, STDERR_FILENO);;
	ft_putendl_fd("malloc error!", STDERR_FILENO);
	exit(0);
}