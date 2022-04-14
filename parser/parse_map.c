/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:31 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:47:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
**                           +--------------------+
**                           |  Iter on command   |
**                           |                    |
**                           +----------+---------+
**                                      |
**                                      |
**                                      |
**                                      |
**                                      |
**                           +----------+---------+
**                           |                    |
**                           |   Command making   |
**                           +------+-------+-----+
** +-----------+                    |       |              +------------------+
** |Extract arg|                    |       |              |                  |
** |           |<-------------------+       +------------> |  EXTRACT REDIRE  |
** |           |                                           |                  |
** +-----+-----+                                           +--------+---------+
**       |                                                          |
**       |                                                          |
**       |                                                          |
** +-----+-----+                                           +--------+---------+
** |           |                                           |Rm quotes expand  |
** |Epand vars |                                           |                  |
** |           |                                           |                  |
** +-----------+                                           +------------------+
*/

char	*slashify_bkslash_line(char **argsline)
{
	int			i;
	t_lexer		*lex;
	t_ops		type;
	char		*dstring;

	i = 0;
	dstring = NULL;
	lex = lexer_init(*argsline);
	while (lex->i < lex->src_size)
	{
		type = lexer_which_op(lex);
		if (type == O_DQUOTE || type == O_SQUOTE)
		{
			parser_handle_quotes(&dstring, type, lex);
			lexer_advance(lex);
			continue ;
		}
		else if (lex->c == '\\')
			dynamic_string2(&dstring, '\\');
		dynamic_string2(&dstring, lex->c);
		lexer_advance(lex);
	}
	lexer_free(&lex);
	ft_memdel((void **)argsline);
	return (dstring);
}

void	after_parser_squote(t_lexer *lex, char **dstring)
{
	lexer_advance(lex);
	while (lexer_which_op(lex) != O_SQUOTE)
	{
		dynamic_string2(dstring, lex->c);
		lexer_advance(lex);
	}
}

void	after_parser_dquote(t_lexer *lex, char **dstring, t_bash *bash)
{
	lexer_advance(lex);
	while (lex->c != '\0' && lexer_which_op(lex) != O_DQUOTE)
	{
		if (lexer_which_op(lex) == O_DOLLAR)
			parse_dollar(lex, dstring, bash);
		else
			dynamic_string2(dstring, lex->c);
		lexer_advance(lex);
	}
}

void	after_parser_expand_loop(char **newarg, t_lexer *lex, t_bash *sh)
{
	t_ops	type;

	type = lexer_which_op(lex);
	if (lex->c != '\\')
	{	
		if (type == O_NONE)
			dynamic_string2(newarg, lex->c);
		else if (type == O_SQUOTE)
			after_parser_squote(lex, newarg);
		else if (type == O_DQUOTE)
			after_parser_dquote(lex, newarg, sh);
	}
	else if (lex->c == '\\')
	{
		lexer_advance(lex);
		dynamic_string2(newarg, lex->c);
	}
	lexer_advance(lex);
}

char	*after_parser_expand(char *arg, t_bash *sh)
{
	char	*newarg;
	t_lexer	*lex;	

	lex = lexer_init(arg);
	newarg = NULL;
	while (lex->i < lex->src_size)
		after_parser_expand_loop(&newarg, lex, sh);
	lexer_free(&lex);
	if (!newarg)
		newarg = ft_strdup("");
	return (newarg);
}
