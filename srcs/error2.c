/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 09:57:58 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/15 10:21:01 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_from_errno(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	error_not_a_dir(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(NOT_A_DIR, STDERR_FILENO);
}

int		error_home_not_set(void)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd("HOME", STDERR_FILENO);
	ft_putendl_fd(" not set", STDERR_FILENO);
	return (1);
}
