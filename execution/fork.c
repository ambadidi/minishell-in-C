/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:29:45 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:29:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	child_execution(t_bash *bash, t_cmdtable *cmd, t_execution *exec)
{
	if (cmd->files)
		opening_files_returnfd(cmd->files, exec);
	if (exec->redirect_fd[0] != 0)
		dup2(exec->redirect_fd[0], 0);
	else if (STDIN_FILENO != exec->pin)
		dup2(exec->pin, STDIN_FILENO);
	if (exec->redirect_fd[1] != 1)
		dup2(exec->redirect_fd[1], 1);
	else if (STDOUT_FILENO != exec->pout)
		dup2(exec->pout, STDOUT_FILENO);
	close(exec->pipe_fd[0]);
	wrapper_exec(cmd, bash);
}

void	last_child_execution_child(t_cmdtable *cmd, t_execution *exec,
		t_bash *bash)
{
	if (cmd->files)
		opening_files_returnfd(cmd->files, exec);
	if (exec->redirect_fd[0] != 0)
		dup2(exec->redirect_fd[0], 0);
	else if (STDIN_FILENO != exec->pin)
		dup2(exec->pin, STDIN_FILENO);
	if (exec->redirect_fd[1] != 1)
		dup2(exec->redirect_fd[1], 1);
	else if (STDOUT_FILENO != exec->pout)
		dup2(exec->pout, STDOUT_FILENO);
	close(exec->pipe_fd[0]);
	wrapper_exec(cmd, bash);
}

void	last_child_execution(t_bash *bash, t_cmdtable *cmd, t_execution *exec)
{
	if (pipe(exec->pipe_fd))
		execution_error(1);
	if (STDOUT_FILENO != exec->pout)
		close(exec->pout);
	exec->pout = STDOUT_FILENO;
	exec->pid = fork();
	if (exec->pid == 0)
		last_child_execution_child(cmd, exec, bash);
	else if (exec->pid > 0)
		exec->array_pids[exec->iter] = exec->pid;
	if (exec->pin != STDIN_FILENO)
		close(exec->pin);
	if (STDOUT_FILENO != exec->pout)
		close(exec->pout);
}

void	execution_loop(t_bash *bash, t_cmdtable *cmd, t_execution *exec)
{
	if (pipe(exec->pipe_fd))
		execution_error(1);
	exec->pout = exec->pipe_fd[WRITE_END];
	exec->pid = fork();
	if (exec->pid == -1)
		execution_error(1);
	if (exec->pid == 0)
		child_execution(bash, cmd, exec);
	close (exec->pipe_fd[1]);
	if (exec->pin != STDIN_FILENO)
		close(exec->pin);
	exec->pin = exec->pipe_fd[READ_END];
	exec->array_pids[exec->iter] = exec->pid;
	exec->iter++;
}

void	execution_start_point(t_bash	*bash)
{
	t_dllnode		*iterator;
	t_cmdtable		*cmd;
	t_execution		*exec;

	iterator = bash->cmds_list;
	exec = execution_struct_init(sizeoflst(iterator));
	exec->iter = 0;
	exec->size = sizeoflst(iterator);
	while (exec->iter < exec->size - 1)
	{
		cmd = iterator->data;
		execution_loop(bash, cmd, exec);
		iterator = iterator->next;
	}
	cmd = iterator->data;
	last_child_execution(bash, cmd, exec);
	if (STDOUT_FILENO != exec->pout)
		close(exec->pout);
	wait_for_childs(exec, bash);
	close(exec->pipe_fd[0]);
	close(exec->pipe_fd[1]);
	if (exec->pin != STDIN_FILENO)
		close(exec->pin);
	execution_struct_destruct(&exec);
}
