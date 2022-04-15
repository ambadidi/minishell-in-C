/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:16 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:20:08 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	after_parser_removequotes(t_dllnode *list_args, t_bash *sh)
{
	t_tokken		*tok;
	char			*str;

	while (list_args)
	{
		tok = list_args->data;
		str = tok->content;
		tok->content = after_parser_expand(tok->content, sh);
		ft_memdel((void **)&str);
		list_args = list_args->next;
	}
}

char	**clone_ll_char(t_dllnode *list_args)
{
	t_tokken		*tok;
	int				size;
	char			**args;
	int				i;	

	i = 0;
	size = sizeoflst(list_args);
	args = malloc((size + 1) * sizeof(char *));
	while (list_args)
	{
		tok = list_args->data;
		args[i] = ft_strdup(tok->content);
		i++;
		list_args = list_args->next;
	}
	args[i] = NULL;
	return (args);
}

t_cmdtable	*cmd_list_creator(t_dllnode *listargs, t_dllnode *listfiles)
{
	t_cmdtable	*cmd;

	cmd = malloc(sizeof(t_cmdtable));
	cmd->cmd_path = NULL;
	cmd->cmd_args = clone_ll_char(listargs);
	cmd->files = listfiles;
	cmd->isbuiltin = FALSE;
	return (cmd);
}

void	cmd_list_destruct(void *_cmd)
{
	t_cmdtable	*cmd;
	int			i;

	cmd = _cmd;
	if (cmd)
	{
		i = 0;
		cmd = _cmd;
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->cmd_args)
		{
			while (cmd->cmd_args[i])
			{
				free(cmd->cmd_args[i]),
				i++;
			}
			free(cmd->cmd_args);
		}
		dl_clear(&(cmd->files), files_destruct);
		free(cmd);
	}	
}

void	prpar_command(t_bash *sh, char *line)
{
	char		*remain;
	char		*expanded;
	t_dllnode	*redirections;
	t_dllnode	*list_args;

	redirections = wraper_get_redirection(sh, line, &remain);
	remain = slashify_bkslash_line(&remain);
	expanded = parser_expand_dollar(&remain, sh);
	ft_memdel((void **)&remain);
	list_args = args_finale(expanded, sh);
	ft_memdel((void **)&expanded);
	after_parser_removequotes(list_args, sh);
	dl_lstaddbac(&(sh->cmds_list), cmd_list_creator(list_args, redirections));
	dl_clear(&list_args, tokken_free);
}
