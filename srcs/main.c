/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 10:32:42 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/10 10:32:44 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_string(char **line)
// {
// 	char *temp = NULL;
// 	int index = 0;
//
// 	while (**line && !is_separator(**line))
// 	{
// 		temp = ft_realloc(temp, 1);
// 		temp[index++] = **line;
// 		(*line)++;
// 	}
// 	return (temp);
// }

char	*get_str_regular(char **line, t_list *env)
{
	char	*temp;
	int		index;

	(void)env;
	index = 0;
	temp = NULL;
	while (**line && !ft_strchr(" <>|;\'\"", **line))
	{
		if (**line == '$')
			; // функция алины
		else if (**line == '\\')
			(*line)++;
		temp = ft_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;

	}
	return (temp);
}

char	*parse_argument(char **line, t_list *env)
{
	char	*temp;
	int		index;
	char	*res;

	res = NULL;
	index = 0;
	temp  = NULL;
	while (**line && !ft_strchr("|><;", **line))
	{
		if (ft_isspace(**line))
			break ;
		if (**line == '\'')
		{
			ft_putendl_fd("одинарные ковычки", 1);
			exit(0) ;
		}
		else if (**line == '\"')
		{
			ft_putendl_fd("двойные ковычки", 1);
			exit(0) ;
		}
		else
			temp = get_str_regular(line, env);
		if (!(res = ft_strjoin_gnl(res, temp)))
			exit(0); // с каким значением?
		free(temp);
	}
	return (res);
}

char	**parse_line(char **line, t_fd *fd_pipe, t_list *env)
{
	char	*str;
	char	**cmd;
	int		i;

	cmd = NULL;
	str = NULL;
	i = 0;
	while (**line)
	{
		while (ft_isspace(**line))
			(*line)++;
		if (!**line || (**line && **line == ';'))
			break;
		if (**line == '|' && cmd)
		{
			ft_putendl_fd("i see pipe", 1);
			get_pipe(fd_pipe, line);
			break;
		}

		// if (**line && is_separator(**line))
		// 	(*line)++;
		// if ((str = get_string(line)))
		if ((str = parse_argument(line, env)))
		{
			cmd = ft_strstr_realloc(cmd, 1);
			cmd[i++] = str;
		}
	}
	return (cmd);
}

void	minishell(char *line, t_list **env)
{
	char	**cmd;
	t_fd	fd_pipe;

	while (*line)
	{
		if (*line == ';')
			(*line)++;
		else
		{
			cmd = parse_line(&line, &fd_pipe, *env);
			if (cmd)
				ft_env(cmd, *env);
			if (cmd && !print_dir(cmd))
			{
				run_command(line, cmd, env);
				ft_free_strstr(cmd);
			}
		}
	}
}

int		main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;

	(void)ac;
	(void)av;
	env = NULL;
	g_question = 0;
	ft_lstadd_back(&env, ft_lstnew(NULL));
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		write_prompt();
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input, &env);
		free(user_input);
	}
	free_env(env);
	return (0);
}
