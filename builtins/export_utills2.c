/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utills2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:27:09 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:27:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_printenv2(t_dllnode *node)
{
	dl_lstiter(node, sfprint2);
}

void	clone_dll_head(char **env, t_dllnode **head_new)
{
	int	i;	

	i = 0;
	if (!env)
	{
		*head_new = NULL;
		return ;
	}
	while (env[i])
	{
		dl_lstaddbac(head_new, envsmake(env[i]));
		i++;
	}
}

void	declare_x(char **env)
{
	t_bash		*bash;
	t_dllnode	*head_env;

	head_env = NULL;
	bash = get_bash__ptr(NULL);
	clone_dll_head(env, &head_env);
	sort_var(head_env);
	ft_printenv2(head_env);
	ft_printenv2(bash->env_useless);
	dl_clear(&head_env, env_free);
}

t_bool	if_env_exist_and_update(t_env *env_new, t_bash *bash)
{
	t_dllnode	*node;
	t_env		*env;
	t_dllnode	*tmp;
	t_env		*env_tmp;	

	env_tmp = NULL;
	tmp = dl_search(bash->env_useless, w_srchenv, env_new->var);
	node = dl_search(bash->env, w_srchenv, env_new->var);
	if (node)
	{
		env = node->data;
		copy_and_delete(&(env->value), env_new->value);
		copy_and_delete(&(env->cmd), env_new->cmd);
		return (TRUE);
	}
	if (ft_strchr(env_new->cmd, '='))
	{
		if (tmp)
			dl_del(&(bash->env_useless), tmp, env_free);
	}
	return (FALSE);
}

int	builtin_export(char **args, char	**env)
{
	t_bash		*bash;
	int			state;

	state = 0;
	bash = get_bash__ptr(NULL);
	if (get_argc(args) == 1)
		declare_x(env);
	else if (get_argc(args) > 1)
	{
		state = loop_on_env(args, bash);
	}
	return (state);
}
