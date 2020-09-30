/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:55:49 by qtamaril          #+#    #+#             */
/*   Updated: 2020/09/30 15:28:34 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(int fd, char **line)
{
	char	buf[2];
	char	*tmp;
	char	*result;

	buf[1] = 0;
	result = NULL;
	while (1)
	{
		tmp = result;
		if (read(fd, buf, 1) == 0)
		{
			if (!tmp)
				break ;
			ft_putstr_fd("  \b\b", fd);
			continue ;
		}
		result = ft_strjoin(result, (*buf == '\n' ? "" : buf));
		if (tmp)
			free(tmp);
		if (*buf == '\n')
			break ;
	}
	*line = result;
}


void	type_prompt(void)
{
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
}

void print_env_list(t_list	*env) {
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		t_env *content = ((t_env*)tmp->content);
		ft_putstr_fd(content->name, STDOUT_FILENO);
		ft_putstr_fd(" = ", STDOUT_FILENO);
		ft_putendl_fd(content->value, STDOUT_FILENO);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **ev)
{
	t_list	*env;
	char	*user_input;

	(void)ac;
	(void)av;
	env = NULL;
	if (!init_env(&env, ev))
		return (0);
	ft_putstr_fd("\e[1;1H\e[2J", STDOUT_FILENO);
	while (1)
	{
		type_prompt();
		read_line(0, &user_input);
		ft_putstr_fd(user_input, STDOUT_FILENO);
	}
	free_env(env);
	// while (1)
	// 	(void)env;
	return (0);
}

// int	main(void)
// {
// 	char *dir = NULL;
//
// 	dir = getcwd(NULL, 0);
// 	ft_putendl_fd(dir, 1);
// 	free(dir);
// 	// if (chdir("sd") == 0)
// 	// {
// 	// 	getcwd(dir, NULL);
// 	// 	ft_putendl_fd(dir, 1);
// 	// }
// 	// else
// 	// {
// 	// 	ft_putendl_fd("no such file or directory:", 1);
// 	// }
// 	//
// 	// struct stat buff;
// 	// int fd = open("includes/minishell.h", O_RDWR);
// 	// (void)fd;
// 	// stat("includes/minishell.h", &buff);
// 	// ft_putnbr_fd(buff.st_mode, 1);
// 	//
// 	// ft_putendl_fd("", 1);
// 	// fstat(fd, &buff);
// 	// ft_putnbr_fd(buff.st_mode, 1);
//
// 	// lstat("includes/minishell.h", &dir);
//
//
// 	while (1)
// 		(void)dir;
//
// 	return (0);
// }
