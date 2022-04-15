/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:32:55 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	lexer_start(t_lexer	*lex,	t_bash *bash)
{
	t_dllnode		**tokken;
	char			*dstring;

	dstring = NULL;
	tokken = &(bash->tokken);
	while (lex->i < lex->src_size)
		lexer_start_loop(&dstring, lex, tokken);
	if (dstring)
	{
		dl_lstaddbac(tokken, tokken_init(dstring, O_WORD));
		free (dstring);
		dstring = NULL;
	}
}

char	lexer_gnc(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		if (lexer->i + 1 < lexer->src_size && lexer->c != '\0')
			return (lexer->src[lexer->i + 1]);
	}
	return ('\0');
}

t_ops	lexer_get_lop(t_dllnode *headoftokens)
{
	t_dllnode		*iterator;
	t_tokken		*this_tokken;

	this_tokken = NULL;
	iterator = headoftokens;
	while (iterator->next)
		iterator = iterator->next;
	if (iterator)
	{
		this_tokken = iterator->data;
		return (this_tokken->type);
	}
	return (O_NIL);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}
