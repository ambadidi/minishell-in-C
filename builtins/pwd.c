/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:27:51 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin_pwd(char **args, char	**env)
{
	char	*s;
	int		flag;

	flag = 0;
	(void)env;
	if (get_argc(args) != 1)
	{
		ft_putendl_fd("No options are allowed in this minishell", 2);
		return (1);
	}
	else
	{
		s = getcwd(NULL, 0);
		flag = errno;
		if (s == NULL)
		{
			strerror(flag);
			return (1);
		}
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		ft_memdel((void **)&s);
		return (1);
	}
}
