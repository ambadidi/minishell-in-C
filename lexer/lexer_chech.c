/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_chech.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:32:29 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:32:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	o_pipe_checker(int prev, int next, t_bash *bash)
{
	if ((next == O_WORD || next == O_ORED || next == O_IRED
			|| next == O_ARED || next == O_SQUOTE || next == O_DQUOTE
			|| next == O_HERE_DOC)
		&& (prev == O_WORD || prev == O_SQUOTE || prev == O_DQUOTE))
		return (SUCCES);
	bash->op_error = O_PIPE;
	return (FAILURE);
}

t_status	checker_p2(int prev, int curr, int next, t_bash *bash)
{
	if (curr == O_PIPE)
		return (o_pipe_checker(prev, next, bash));
	if (curr == O_IRED)
		return (o_ired_checker(prev, next, bash));
	if (curr == O_ORED)
		return (o_ored_checker(prev, next, bash));
	if (curr == O_ARED)
		return (o_ared_checker(prev, next, bash));
	if (curr == O_HERE_DOC)
		return (heredoc_checker(prev, next, bash));
	return (SUCCES);
}

t_status	checker(t_dllnode *node, t_bash *bash)
{
	t_tokken	*cur;
	t_tokken	*tmp;
	int			next;
	int			prev;

	next = 0;
	prev = 0;
	if (node->next)
	{
		tmp = node->next->data;
		next = tmp->type;
	}
	if (node->prev)
	{
		tmp = node->prev->data;
		prev = tmp->type;
	}
	cur = node->data;
	return (checker_p2(prev, cur->type, next, bash));
}

t_status	check_syntax(t_bash *bash)
{
	t_dllnode		*node;
	int				health;

	health = SUCCES;
	node = bash->tokken;
	while (node)
	{
		if (checker(node, bash) == FAILURE)
		{
			health = FAILURE;
			break ;
		}
		node = node->next;
	}
	return (health);
}
