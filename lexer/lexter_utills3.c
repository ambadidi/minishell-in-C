/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexter_utills3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:30 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:33:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_status	o_ired_checker(int prev, int next, t_bash *bash)
{
	(void)prev;
	if (next == O_WORD || next == O_SQUOTE || next == O_DQUOTE)
		return (SUCCES);
	bash->op_error = O_IRED;
	return (FAILURE);
}

t_status	o_ared_checker(int prev, int next, t_bash *bash)
{
	(void)prev;
	if (next == O_WORD || next == O_SQUOTE || next == O_DQUOTE)
		return (SUCCES);
	bash->op_error = O_ARED;
	return (FAILURE);
}

t_status	heredoc_checker(int prev, int next, t_bash *bash)
{
	(void)prev;
	if (next == O_WORD || next == O_SQUOTE || next == O_DQUOTE)
		return (SUCCES);
	bash->op_error = O_HERE_DOC;
	return (FAILURE);
}

t_status	o_ored_checker(int prev, int next, t_bash *bash)
{
	(void)prev;
	if (next == O_WORD || next == O_SQUOTE || next == O_DQUOTE)
		return (SUCCES);
	bash->op_error = O_ORED;
	return (FAILURE);
}

t_status	o_semi_checker(int prev, int next, t_bash *bash)
{
	(void)next;
	if (prev == O_WORD || prev == O_SQUOTE || prev == O_DQUOTE)
		return (SUCCES);
	bash->op_error = O_SEMI;
	return (FAILURE);
}
