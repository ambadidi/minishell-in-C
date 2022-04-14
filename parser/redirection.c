/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:51 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:47:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ops	next_expected_type(t_ops curr)
{
	if (curr == O_HERE_DOC)
		return (F_HEREDOC);
	else if (curr == O_IRED)
		return (F_INPUT);
	else if (curr == O_ORED)
		return (F_OUTPUT);
	else if (curr == O_ARED)
		return (F_APPEND);
	return (O_NIL);
}

void	specify_redirection(t_dllnode *tokkens)
{
	t_tokken	*temp;
	t_tokken	*next;

	while (tokkens)
	{
		temp = tokkens->data;
		if (temp->type == O_HERE_DOC || temp->type == O_ARED
			|| temp->type == O_IRED || temp->type == O_ORED)
		{
			next = tokkens->next->data;
			next->type = next_expected_type(temp->type);
			tokkens = tokkens->next;
		}
		tokkens = tokkens->next;
	}
}

t_dllnode	*extract_redirections(t_dllnode *parsed)
{
	t_dllnode	*new_list;
	t_tokken	*temp;

	new_list = NULL;
	while (parsed)
	{
		temp = parsed->data;
		if (temp->type == F_APPEND || temp->type == F_OUTPUT
			|| temp->type == F_INPUT || temp->type == F_HEREDOC)
			dl_lstaddbac(&new_list, files_constr(temp->type, temp->content));
		parsed = parsed->next;
	}
	return (new_list);
}
