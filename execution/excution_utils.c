/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:28:48 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:14:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_builtin_parrent(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "exit") == 0
			|| ft_strcmp(cmd, "unset") == 0
			|| ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "export") == 0)
			return (TRUE);
	}
	return (FALSE);
}

t_bool	is_builtin(char *cmd)
{
	if (cmd)
	{
		if (ft_strcmp(cmd, "exit") == 0
			|| ft_strcmp(cmd, "env") == 0
			|| ft_strcmp(cmd, "unset") == 0
			|| ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "echo") == 0
			|| ft_strcmp(cmd, "pwd") == 0
			|| ft_strcmp(cmd, "export") == 0)
			return (TRUE);
	}
	return (FALSE);
}
