/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:32:39 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ops_to_string(t_ops op)
{
	if (op == O_NONE)
		return (NULL);
	if (op == O_PIPE)
		return ("|");
	if (op == O_IRED)
		return ("<");
	if (op == O_ARED)
		return (">>");
	if (op == O_ORED)
		return (">");
	if (op == O_WORD)
		return ("O_WORD");
	if (op == O_HERE_DOC)
		return ("<<");
	return (NULL);
}

t_status	lex_errors(t_bash *sh)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	ft_putstr_fd(ops_to_string(sh->op_error), 2);
	ft_putstr_fd("\'\n", 2);
	sh->op_error = O_NONE;
	return (FAILURE);
}
