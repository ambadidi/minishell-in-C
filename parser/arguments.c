/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:04 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:46:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parser_handle_quotes(
	char **dstring,
	t_ops type,
	t_lexer *lex
)
{
	char	c;

	c = lex->c;
	(void)type;
	dynamic_string2(dstring, lex->c);
	lexer_advance(lex);
	while (lex->i < lex->src_size)
	{
		if (lex->c == c)
			break ;
		dynamic_string2(dstring, lex->c);
		lexer_advance(lex);
	}
	dynamic_string2(dstring, lex->c);
}

void
	args_finale_loop(t_dllnode **tokken, t_lexer *lex, char **dstring)
{
	t_ops	type;

	type = lexer_which_op(lex);
	if (lex->c == '\\')
	{
		dynamic_string2(dstring, lex->c);
		lexer_advance(lex);
		dynamic_string2(dstring, lex->c);
	}
	else if (type == O_NONE || type == O_DOLLAR)
		dynamic_string2(dstring, lex->c);
	else if (type == O_DQUOTE || type == O_SQUOTE)
		parser_handle_quotes(dstring, type, lex);
	else if (type != O_NONE && type != O_DQUOTE && type != O_SQUOTE)
	{
		if (*dstring)
			dl_lstaddbac(tokken, tokken_init(*dstring, O_WORD));
		if (type != O_SPACE)
			dl_lstaddbac(tokken, tokken_init(ops_to_string(type), type));
		ft_memdel((void **)dstring);
	}
	lexer_advance(lex);
}

t_dllnode	*args_finale(char *sh, t_bash *bash)
{
	t_dllnode		*tokken;
	char			*dstring;
	t_lexer			*lex;

	(void)bash;
	dstring = NULL;
	tokken = NULL;
	if (sh == NULL)
		return (NULL);
	lex = lexer_init(sh);
	while (lex->i < lex->src_size)
		args_finale_loop(&tokken, lex, &dstring);
	if (dstring)
	{
		dl_lstaddbac(&tokken, tokken_init(dstring, O_WORD));
		ft_memdel((void **)&dstring);
	}
	lexer_free(&lex);
	return (tokken);
}
