/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:29:22 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:29:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**point_to_env(t_dllnode	*env)
{
	t_env		*tokken;
	int			size;
	char		**env_cpy;
	int			index;

	index = 0;
	size = sizeoflst(env);
	if (size == 0)
		return (NULL);
	env_cpy = (char **)malloc(sizeof(char *) * (size + 1));
	while (env)
	{
		tokken = env->data;
		env_cpy[index] = tokken->cmd;
		env = env->next;
		index++;
	}
	env_cpy[index] = NULL;
	return (env_cpy);
}

int	builtin_execution(char **args, char **env)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, env));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args, env));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, env));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, env));
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, env));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, env));
	return (0);
}

void	execute_one_cmd(t_cmdtable	*cmdtable, t_bash *bash)
{
	int				status;

	status = 0;
	if (is_builtin(cmdtable->cmd_args[0]) == TRUE)
		status = builtin_execution(cmdtable->cmd_args, bash->env_array);
	bash->exit_code = status;
}

void	execute_n_cmds(t_bash *bash)
{
	t_dllnode	*node;
	t_cmdtable	*cmd;

	node = bash->cmds_list;
	(void)cmd;
	cmd = node->data;
	if (node->next == NULL && is_builtin(cmd->cmd_args[0]) == TRUE
		&& is_builtin_parrent(cmd->cmd_args[0]) == TRUE && cmd->files == NULL)
	{
		execute_one_cmd(cmd, bash);
	}
	else
		execution_start_point(bash);
}

void	execute_on_cmd(t_bash *bash)
{
	here_doc_init(bash);
	execute_n_cmds(bash);
}
