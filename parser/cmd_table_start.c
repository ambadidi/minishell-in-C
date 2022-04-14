/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:19 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:46:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_tok_start_loop(t_lexer *lex, char **dstring, t_dllnode **tokken)
{
	t_ops			type;

	type = lexer_which_op(lex);
	if (type == O_NONE || type == O_DOLLAR)
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

t_dllnode	*cmd_tokken_start(t_lexer *lex, t_bash *bash)
{
	t_dllnode		*tokken;
	char			*dstring;

	(void)bash;
	dstring = NULL;
	tokken = NULL;
	while (lex->i < lex->src_size)
		cmd_tok_start_loop(lex, &dstring, &tokken);
	if (dstring)
	{
		dl_lstaddbac(&tokken, tokken_init(dstring, O_WORD));
		ft_memdel((void **)&dstring);
	}
	return (tokken);
}
