/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excution_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:29:06 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execution_struct_destruct(t_execution **exec)
{
	t_execution		*exec_;

	exec_ = *exec;
	if (exec_)
	{
		if (exec_->array_pids)
			free(exec_->array_pids);
		free(exec_);
	}
	exec_ = NULL;
	exec = NULL;
}

void	wait_for_childs(t_execution *exec, t_bash *bash)
{
	int		i;
	int		status;

	i = 0;
	g_pid = 0;
	while (i < exec->size)
	{
		g_pid = exec->array_pids[i];
		waitpid(exec->array_pids[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			status = WTERMSIG(status);
			if (status == SIGQUIT)
				dprintf(2, "\\Quit: 3\n");
			if (status != 131)
				status += 128;
		}
		i++;
		++g_pid;
	}
	g_pid = 0;
	bash->exit_code = status;
}
