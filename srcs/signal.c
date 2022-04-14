/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:48:45 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:48:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler_sigint(int sig)
{
	t_bash	*bash;

	bash = get_bash__ptr(NULL);
	(void)sig;
	if (g_pid == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		bash->exit_code = 1;
	}
}

void	signal_handler_sigquit(int sig)
{
	(void)sig;
	if (g_pid == 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
