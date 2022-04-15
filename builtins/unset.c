/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:28:11 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_unset(char **args, char	**env)
{
	int			i;
	t_dllnode	*head;
	t_bash		*sh;
	int			state;

	(void)env;
	i = 0;
	sh = get_bash__ptr(NULL);
	state = 0;
	while (args[i])
	{	
		if (!if_var_valid(args[i]) || !if_prefix_valid(args[i]))
		{
			ft_putendl_fd("export: invalid argument", 2);
			state = 1;
		}
		head = dl_search(sh->env, w_srchenv, args[i]);
		if (head)
		{
			dl_del(&(sh->env), head, env_free);
			return (0);
		}
		i++;
	}
	return (state);
}
