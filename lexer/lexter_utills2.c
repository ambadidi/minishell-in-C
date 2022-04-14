/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexter_utills2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:20 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:18:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*dynamic_string(char *dest, char newchar)
{
	char	*newdest;
	int		i;
	int		size;

	size = ft_strlen(dest);
	i = 0;
	newdest = NULL;
	newdest = malloc(sizeof(char) * (size + 2));
	if (!newdest)
		return (NULL);
	while (i < size)
	{
		newdest[i] = dest[i];
		i++;
	}
	newdest[i] = newchar;
	newdest[i + 1] = '\0';
	return (newdest);
}

char	*nulled_strdup(char	*str)
{
	if (!str)
		return (ft_strdup(""));
	else
		return (ft_strdup(str));
}

t_lexer	*lexer_init(char	*line)
{
	t_lexer		*lex;

	lex = calloc(1, sizeof(t_lexer));
	lex->src_size = ft_strlen(line);
	lex->src = nulled_strdup(line);
	lex->i = 0;
	lex->c = lex->src[lex->i];
	return (lex);
}

void	lexer_free(t_lexer **lex)
{
	if (*lex)
	{
		if ((*lex)->src)
			free((*lex)->src);
		free(*lex);
	}
	*lex = NULL;
}

void	lexer_start_loop(char **dstring, t_lexer *lex, t_dllnode **tokken)
{
	t_ops		type;

	type = lexer_which_op(lex);
	if (type == O_NONE || type == O_DOLLAR)
		dynamic_string2(dstring, lex->c);
	else if (type == O_DQUOTE || type == O_SQUOTE)
	{
		lex_handle_quotes(dstring, type, lex);
	}
	else if (type != O_NONE && type != O_DQUOTE && type != O_SQUOTE)
	{
		if (*dstring)
			dl_lstaddbac(tokken, tokken_init(*dstring, O_WORD));
		if (type != O_SPACE)
			dl_lstaddbac(tokken, tokken_init(ops_to_string(type), type));
		if (*dstring)
			free (*dstring);
		*dstring = NULL;
	}				
	lexer_advance(lex);
}
