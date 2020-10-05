/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtamaril <qtamaril@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:35:02 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 13:43:32 by qtamaril         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_list_elem(t_list *env, t_list *list_prev)
{
	t_list	*temp_element;
	t_env	*content;

	content = (t_env*)env->content;
	if (content)
	{
		free(((t_env*)env->content)->name);
		free(((t_env*)env->content)->value);
		free((t_env*)env->content);
	}
	if (list_prev)
	{
		list_prev->next = env->next;
		free(env);
	}
	else if (env->next)
	{
		temp_element = env->next;
		env->content = env->next->content;
		env->next = env->next->next;
		free(temp_element);
	}
	// else if (ft_lstsize(env) == 1)
	// {
	// 	free(env);
	// }
	// 	ft_lstclear(&env, NULL);
	// else
	// 	free(env);
}

// unset Apple_PubSub_Socket_Render; unset TERM; unset LANG; unset SHELL; unset SECURITYSESSIONID; unset TMPDIR; unset XPC_FLAGS; unset XPC_SERVICE_NAME; unset TERM_PROGRAM; unset TERM_PROGRAM_VERSION; unset TERM_SESSION_ID; unset HOME; unset LOGNAME; unset USER; unset PATH; unset SHLVL; unset PWD; unset OLDPWD; unset _

void	my_unset(t_list *env, char **vars)
{
	t_env	*curr_env;
	t_list 	*list_prev;
	// int		i;

	list_prev = NULL;
	while (env)
	{
		curr_env = (t_env*)env->content;
		// i = 1;
		// while (vars[i])
		// {
			if (!ft_strcmp(curr_env->name, vars[1]))
			{
				remove_list_elem(env, list_prev);

				ft_putendl_fd("", 1);
				ft_putnbr_fd(ft_lstsize(env), 1);
				ft_putendl_fd("", 1);

				// my_env(env);
				break ;
			}
		// 	i++;
		// }
		list_prev = env;
		env = env->next;
	}
	// return (1);
}
