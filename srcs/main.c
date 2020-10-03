/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:55:49 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/03 18:52:11 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_prompt(void)
{
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
}

// void print_env_list(t_list	*env) {
// 	t_list	*tmp;
//
// 	tmp = env;
// 	while (tmp)
// 	{
// 		t_env *content = ((t_env*)tmp->content);
// 		ft_putstr_fd(content->name, STDOUT_FILENO);
// 		ft_putstr_fd(" = ", STDOUT_FILENO);
// 		ft_putendl_fd(content->value, STDOUT_FILENO);
// 		tmp = tmp->next;
// 	}
// }

int		is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>' || c == '|' || c == ';' || c == '\'' \
	|| c == '\"')
		return (1);
	return (0);
}

char	*get_string(char **line)
{
	char *temp = NULL;
	int index = 0;

	while (**line && !is_separator(**line))
	// while (**line && !ft_strchr(" <>|;\'\"", **line))
	{
		temp = ft_realloc(temp, 1);
		temp[index++] = **line;
		(*line)++;
	}
	return (temp);
}

void	parse_line(char **line)
{
	char	*str;
	char	**args;
	int		i;

	args = NULL;
	str = NULL;
	i = 0;
	while (**line)
	{
		while (**line == ' ')
			(*line)++;
		if (!**line || **line == ';')
			break;
		if (**line && is_separator(**line))
			(*line)++;
		if ((str = get_string(line)))
		{
			args = ft_strstr_realloc(args, 1);
			args[i++] = str;
		}
	}
	ft_putstrstr_fd(args, STDOUT_FILENO);
	ft_free_strstr(args);
}

void	minishell(char *line)
{
	while (*line)
	{
		if (*line == ';')
			(*line)++;
		else
		{
			parse_line(&line);
			ft_putendl_fd("--------", STDOUT_FILENO);
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
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd(CLEAN, STDOUT_FILENO);
	while (1)
	{
		write_prompt();
		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
			minishell(user_input);
		free(user_input);
	}
	free_env(env);
	return (0);
}
