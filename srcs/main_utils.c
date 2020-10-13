/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:46 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/13 15:57:34 by fkathryn         ###   ########.fr       */
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

int		check_dir_in_begin(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '|' && (*(*line + 1) == '|'))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `||\'", 1);
		return (0);
	}
	else if (**line == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 1);
		return (0);
	}
	return (1);
}
