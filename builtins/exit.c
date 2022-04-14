/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:26:14 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:26:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*zeros_bypasser(char *args)
{
	char	*srt;
	int		i;

	i = 0;
	while (args[i] != '\0' && args[i] == '0')
		i++;
	if (args[i] == '\0')
		return (NULL);
	srt = ft_strdup(&args[i]);
	return (srt);
}

t_bool	check_if_all_degits(char *args)
{
	int	i;

	i = 0;
	if (args[0] == '-' || args[0] == '+')
		i++;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	ft_real_exit(char *msg, int i)
{
	ft_putendl_fd(msg, 2);
	exit(i);
}

int	ft_exit(char **args)
{
	int				status;
	unsigned int	return_value;
	char			*str;

	status = get_bash__ptr(NULL)->exit_code;
	if (get_argc(args) == 2)
	{
		str = zeros_bypasser(args[1]);
		if (str && ft_strlen(str) > 20)
		{
			status = ft_atoi(str);
			ft_real_exit("exit : argument(s) : invalid", status);
		}
	}
	if (get_argc(args) == 2)
	{
		return_value = ft_atoi(args[1]);
		exit (return_value);
	}
	exit (status);
}

int	builtin_exit(char **args, char	**env)
{
	int				*status;

	(void)env;
	status = &(get_bash__ptr(NULL)->exit_code);
	if (get_argc(args) > 2)
	{
		if (check_if_all_degits(args[1]) == FALSE)
		{
			*status = 255;
			ft_putendl_fd("exit: numeric argument required", 2);
			exit(*status);
		}
		else
		{
			*status = 1;
			ft_putendl_fd("exit: too many arguments", 2);
			return (*status);
		}
	}
	else
		ft_exit(args);
	return (0);
}
