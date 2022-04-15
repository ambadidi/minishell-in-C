/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:45 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:21:48 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_ameta(char *input, int i)
{
	if ((input[i] == '<' || (input[i] == '>' && input[i + 1] != '>'
				&& input[i - 1] != '>')
			|| (input[i] == '>' && input[i + 1] == '>' && input[i])
			|| input[i] == '<'
			|| input[i] == '|' || input[i] == ';')
		&& is_metachar(input, i) == TRUE)
		return (TRUE);
	return (FALSE);
}

void	lex_handle_quotes(char **dstring, t_ops type, t_lexer *lex)
{
	char	c;

	c = lex->c;
	dynamic_string2(dstring, lex->c);
	(void)type;
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

char	*parser_expand_dollar(char **args, t_bash *sh)
{
	char		*args_;
	t_lexer		*lex;
	t_ops		type;
	char		*dstring;

	args_ = *args;
	dstring = NULL;
	if (*args == NULL)
		return (NULL);
	lex = lexer_init(args_);
	while (lex->i < lex->src_size)
	{
		type = lexer_which_op(lex);
		if (type == O_DOLLAR)
			parse_dollar(lex, &dstring, sh);
		else if (type == O_SQUOTE || type == O_DQUOTE)
			parser_handle_quotes(&dstring, type, lex);
		else
			dynamic_string2(&dstring, lex->c);
		lexer_advance(lex);
	}
	lexer_free(&lex);
	return (dstring);
}
