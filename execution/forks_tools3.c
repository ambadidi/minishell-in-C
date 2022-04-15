/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_tools3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 20:32:20 by ybarhdad          #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	lets_try_expand(char *path, char **cmd)
{
	char		*tstring;
	t_lexer		*lexer;
	t_bash		*bash;

	(void)cmd;
	tstring = NULL;
	bash = get_bash__ptr(NULL);
	lexer = lexer_init(path);
	while (lexer->i < lexer->src_size)
	{
		if (lexer->src[lexer->i] == '"')
			parser_handle_quotes(&tstring, O_DQUOTE, lexer);
		else if (lexer->src[lexer->i] == '\'')
			parser_handle_quotes(&tstring, O_SQUOTE, lexer);
		else if (lexer->src[lexer->i] == '$')
			parse_dollar(lexer, &tstring, bash);
		else
			dynamic_string2(&tstring, lexer->src[lexer->i]);
		lexer_advance(lexer);
	}
	lexer_free(&lexer);
	if (if_spaces(tstring) == TRUE)
		ft_real_exit("bash: ambiguous redirect", 1);
	*cmd = after_parser_expand(tstring, bash);
	return (TRUE);
}

void	*opening_files_returnfd(t_dllnode *file, t_execution *exec)
{
	int			*fd;
	t_files		*tmp;

	fd = exec->redirect_fd;
	fd[0] = 0;
	fd[1] = 1;
	while (file)
	{
		tmp = file->data;
		if (tmp->type == F_HEREDOC)
			fd[0] = child_open_fd(tmp->path, O_RDONLY);
		else if (tmp->type == F_INPUT)
			fd[0] = child_open_fd(tmp->value, O_RDONLY);
		else if (tmp->type == F_OUTPUT)
			fd[1] = child_open_fd(tmp->value, O_WRONLY | O_CREAT | O_TRUNC);
		else if (tmp->type == F_APPEND)
			fd[1] = child_open_fd(tmp->value, O_WRONLY | O_CREAT | O_APPEND);
		file = file->next;
	}
	return (fd);
}

void	handle_exceve(char *path, char **argv, char **env)
{
	if (*argv == NULL)
		exit(0);
	if (is_builtin(argv[0]))
		handle_execution_builin(argv, env);
	execve(path, argv, env);
	error_management(path);
	execution_error(127);
}

void	wrapper_exec(t_cmdtable *cmd, t_bash *bash)
{
	if (cmd->cmd_args)
	{
		if (cmd->cmd_args[0] != NULL && isadirectory(cmd->cmd_args[0]) == FALSE)
		{
			if (cmd->cmd_args[0][0] == '\0')
			{
				ft_putendl_fd("bash : : command not found", 2);
				exit(127);
			}
			cmd->cmd_path = get_path_cmd(cmd->cmd_args[0], bash->path);
		}
		else if (cmd->cmd_args[0] != NULL && isadirectory(cmd->cmd_args[0])
			== TRUE)
			cmd->cmd_path = cmd->cmd_args[0];
		handle_exceve(cmd->cmd_path, cmd->cmd_args, bash->env_array);
	}
}

t_execution	*execution_struct_init(int size)
{
	t_execution		*exec;

	exec = (t_execution *)malloc(sizeof(t_execution));
	if (!exec)
		execution_error(1);
	exec->array_pids = malloc(sizeof(int) * size);
	if (!exec->array_pids)
		execution_error(1);
	exec->pin = 0;
	exec->pout = 1;
	exec->redirect_fd[0] = 0;
	exec->redirect_fd[1] = 1;
	return (exec);
}
