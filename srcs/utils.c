/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 10:44:46 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/17 15:03:00 by qtamaril         ###   ########.fr       */
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
		g_status = 258;
		return (0);
	}
	else if (**line == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|\'", 1);
		g_status = 258;
		return (0);
	}
	return (1);
}

int		check_redirs(char **line)
{
	int		count;

	count = 0;
	while (**line && **line == '>')
	{
		count++;
		(*line)++;
	}
	if (count == 1)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>\'", 1);
		g_redir_error = 1;
		g_status = 258;
		return (0);
	}
	else if (count > 1)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `>>\'", 1);
		g_status = 258;
		g_redir_error = 1;
		return (0);
	}
	return (1);
}

void	set_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
}
