/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:55:49 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/01 16:38:09 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_prompt(void)
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

// int main(int ac, char **av, char **ev)
// {
// 	t_list	*env;
// 	char	*user_input;
//
// 	(void)ac;
// 	(void)av;
// 	env = NULL;
// 	if (!init_env(&env, ev))
// 		return (0);
// 	ft_putstr_fd(CLEAN, STDOUT_FILENO);
// 	while (1)
// 	{
// 		write_prompt();
// 		if (get_next_line(STDOUT_FILENO, &user_input) == 1)
// 			ft_putendl_fd(user_input, STDOUT_FILENO);
// 		free(user_input);
// 	}
// 	free_env(env);
// 	return (0);
// }

void handler_sigint(int sig)
{
	(void)sig;
	ft_putendl_fd(" Ctrl + C not allowed", STDOUT_FILENO);
}

int	main(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	(void)ev;

	// struct sigaction sa;
	// sa.sa_handler = &handler_sigtstp;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGTSTP, &sa, NULL);

	signal(SIGINT, handler_sigint);

	char letter;
	read(STDIN_FILENO, &letter, 1);
	return (0);
}
