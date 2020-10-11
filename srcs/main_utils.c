/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:46 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/11 15:28:35 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_prompt(void)
{
	char	*path;

	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd("minishell:~", STDOUT_FILENO);
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd(" ", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	free(path);
}

// int				is_separator(char c)
// {
// 	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == ';' || c == '\'' \
// 	|| c == '\"')
// 		return (1);
// 	return (0);
// }

// int		print_dir(char **cmd) //tmp function
// {
// 	if (cmd[0][0] == '/' && cmd[0][1] != 'p')
// 	{
// 		ft_putstr_fd(SHELL, STDERR_FILENO);
// 		ft_putstr_fd(cmd[0], STDERR_FILENO);
// 		ft_putendl_fd(IS_A_DIR, STDERR_FILENO);
// 		ft_free_strstr(cmd);
// 		return (1);
// 	}
// 	else if (cmd[0][0] == '/' && cmd[0][1] == 'p')
// 	{
// 		ft_putstr_fd(SHELL, STDERR_FILENO);
// 		ft_putstr_fd(cmd[0], STDERR_FILENO);
// 		ft_putendl_fd(P_DEN, STDERR_FILENO);
// 		ft_free_strstr(cmd);
// 		return (1);
// 	}
// 	return (0);
// }
