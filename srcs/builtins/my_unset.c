/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkathryn <fkathryn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:35:02 by qtamaril          #+#    #+#             */
/*   Updated: 2020/10/05 15:30:54 by fkathryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_list_elem(t_list **env, t_list *list_prev)
{
	t_list	*temp_element;
	//t_env	*content;

	//content = (t_env*)env->content;
	//if (content)
	//{
	free(((t_env*)(*env)->content)->name);
	((t_env*)(*env)->content)->name = NULL;
	free(((t_env*)(*env)->content)->value);
	((t_env*)(*env)->content)->value = NULL;
	free((t_env*)(*env)->content);
	//}	
	if (list_prev)
	{
		list_prev->next = (*env)->next;
		free(*env);
		*env = NULL;
	}
	else if ((*env)->next)
	{
		temp_element = (*env)->next;
		(*env)->content = (*env)->next->content;
		(*env)->next = (*env)->next->next;
		free(temp_element);
		temp_element = NULL;
	}
	else if (ft_lstsize(*env) == 1)
	{
		free(*env);
		*env = NULL;
	}
	// 	ft_lstclear(&env, NULL);
	// else
	// 	free(env);
}

// unset Apple_PubSub_Socket_Render; unset TERM; unset LANG; unset SHELL; unset SECURITYSESSIONID; unset TMPDIR; unset XPC_FLAGS; unset XPC_SERVICE_NAME; unset TERM_PROGRAM; unset TERM_PROGRAM_VERSION; unset TERM_SESSION_ID; unset HOME; unset LOGNAME; unset USER; unset PATH; unset SHLVL; unset PWD; unset OLDPWD; unset _
// unset __CF_USER_TEXT_ENCODING; unset SSH_AUTH_SOCK; unset HOMEBREW_CACHE; unset HOMEBREW_TEMP; unset LESS; unset LSCOLORS; unset PAGER;

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", ((t_env*)lst->content)->name);
		lst = lst->next;
	}
}

void	my_unset(t_list *env, char **vars)
{
	t_env	*curr_env;
	t_list 	*list_prev;
	// int		i;

	//print_list(env);
	list_prev = NULL;
	ft_putnbr_fd(ft_lstsize(env), 1);
	ft_putendl_fd("", 1);
	while (env)
	{
		curr_env = (t_env*)env->content;
		// i = 1;
		// while (vars[i])
		// {
			if (!ft_strcmp(curr_env->name, vars[1]))
			{
				remove_list_elem(&env, list_prev);

				// ft_putendl_fd("", 1);

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
