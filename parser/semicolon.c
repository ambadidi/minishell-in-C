/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:48:00 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:17:30 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	isnotquoted(char *line, int i, char q)
{
	int		line_size;
	int		j;
	t_bool	flag;

	j = 0;
	flag = FALSE;
	line_size = ft_strlen(line);
	while (j < line_size)
	{
		if (line[j] == q)
		{
			if (flag == FALSE)
				flag = TRUE;
			else
				flag = TRUE;
		}
		if (i == j)
			break ;
		j++;
	}
	if (flag == FALSE)
		return (TRUE);
	return (FALSE);
}

void	split_pipe_loop(t_lexer *lex, char **dstring, t_dllnode **tokken)
{
	if (lex->src[lex->i] == '|')
	{
		dl_lstaddbac(tokken, ft_strdup(*dstring));
		if (*dstring)
			free (*dstring);
		*dstring = NULL;
	}
	else if (lex->src[lex->i] == '\'' || lex->src[lex->i] == '"')
		lex_handle_quotes(dstring, O_DQUOTE, lex);
	else
		dynamic_string2(dstring, lex->c);
	lexer_advance(lex);
}

void	pipe_split(
	t_lexer *lex,
	t_bash *bash
)
{
	t_dllnode		**tokken;
	char			*dstring;

	dstring = NULL;
	tokken = &(bash->pipe_line);
	while (lex->i < lex->src_size)
		split_pipe_loop(lex, &dstring, tokken);
	if (dstring)
	{
		dl_lstaddbac(tokken, ft_strdup(dstring));
		if (dstring)
			free (dstring);
		dstring = NULL;
	}
}
