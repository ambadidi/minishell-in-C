/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:27:31 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sfprint2(void *c)
{
	if (ft_strchr(((t_env *)c)->cmd, '='))
		printf("declare -x %s=\"%s\"\n", ((t_env *)c)->var, ((t_env *)c)->value);
	else
		printf("declare -x %s\n", ((t_env *)c)->var);
	fflush(stdout);
}

int	env_cmp(t_dllnode *a, t_dllnode *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = a->data;
	env_b = b->data;
	return (ft_strcmp(env_a->var, env_b->var));
}

void	env_free(void	*env)
{
	t_env	*t;

	t = env;
	if (t)
	{
		if (t->var)
			free(t->var);
		if (t->value)
			free(t->value);
		if (t->cmd)
			free(t->cmd);
	}
	free(t);
}

void	env_swap(t_dllnode *a, t_dllnode *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = a->data;
	env_b = b->data;
	a->data = env_b;
	b->data = env_a;
}

void	sort_var(t_dllnode *node)
{
	int			swapped;
	t_dllnode	*tmp;

	if (node == NULL)
		return ;
	swapped = 1;
	while (1)
	{
		swapped = 0;
		tmp = node;
		while (tmp)
		{
			if (tmp->next && env_cmp(tmp, tmp->next) > 0)
			{
				env_swap(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		if (swapped == 0)
			break ;
	}
}
