/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexter_utills1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:04 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	is_metachar(char *s, int j)
{
	int		i;

	i = 0;
	if (j == 0)
		return (TRUE);
	j--;
	while (s[j] && s[j] == '\\')
	{
		i++;
		j--;
		if (j < 0)
			break ;
	}
	if (i % 2 == 0)
		return (TRUE);
	else
		return (FALSE);
}

void	dynamic_string2(char **dest, char newchar)
{
	char	*newdest;
	int		i;
	int		size;
	char	*tmp;

	tmp = *dest;
	size = ft_strlen(*dest);
	i = 0;
	newdest = NULL;
	newdest = malloc(sizeof(char) * (size + 2));
	if (!newdest)
		return ;
	while (i < size)
	{
		newdest[i] = (*dest)[i];
		i++;
	}
	newdest[i] = newchar;
	newdest[i + 1] = '\0';
	*dest = newdest;
	if (tmp)
		free(tmp);
}

void	lexer_skip_white_spaces(t_lexer *lexer)
{
	while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' '
		|| lexer->c == '\t')
		lexer_advance(lexer);
}

t_ops	lexer_ischar_op(char c)
{
	if (c == '>')
		return (O_ORED);
	else if (c == '<')
		return (O_IRED);
	else if (c == '|')
		return (O_PIPE);
	else if (c == ' ')
		return (O_SPACE);
	else if (c == '$')
		return (O_DOLLAR);
	else if (c == '\'')
		return (O_SQUOTE);
	else if (c == '"')
		return (O_DQUOTE);
	else
		return (O_NONE);
}

t_ops	lexer_which_op(t_lexer *lex)
{
	if (lex->c == '>' && lex->src[(lex->i + 1)]
		&& lex->src[(lex->i + 1)] == '>')
	{
		lexer_advance(lex);
		return (O_ARED);
	}
	else if (lex->c == '>')
		return (O_ORED);
	else if (lex->c == '<' && lex->src[(lex->i + 1)]
		&& lex->src[(lex->i + 1)] == '<')
	{
		lexer_advance(lex);
		return (O_HERE_DOC);
	}
	else if (lex->c == '<')
		return (O_IRED);
	else if (lex->c == '|')
		return (O_PIPE);
	else if (lex->c == ' ')
		return (O_SPACE);
	else if (lex->c == '$')
		return (O_DOLLAR);
	return ((lex->c == '"') * O_DQUOTE + (lex->c == '\'') * O_SQUOTE);
}
