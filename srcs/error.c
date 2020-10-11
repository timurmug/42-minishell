/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:50:28 by fkathryn          #+#    #+#             */
/*   Updated: 2020/10/11 15:41:19 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_error()
{
	ft_putstr_fd(SHELL, STDERR_FILENO);;
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(0);
}

void	error_print(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	error_is_a_dir(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(IS_A_DIR, STDERR_FILENO);
}

void	error_perm_denied(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(P_DEN, STDERR_FILENO);
}

void	error_no_file_or_dir(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(NO_FILE_DIR, STDERR_FILENO);
}

void	error_cmd_not_found(char *param)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putendl_fd(CMD_NOT_FOUND, STDERR_FILENO);
}
