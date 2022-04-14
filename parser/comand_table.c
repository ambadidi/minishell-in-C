/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:28 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:46:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*search_string_env(char *tosearch, t_bash *sh)
{
	t_dllnode		*node;
	t_env			*env;

	if (tosearch == NULL)
		return (NULL);
	node = dl_search(sh->env, w_srchenv, tosearch);
	if (!node)
		return (NULL);
	env = node->data;
	return (env->value);
}

char	*collect_variable(t_lexer	*lex)
{
	char		*var;

	var = NULL;
	while (lex->i < lex->src_size)
	{
		if (ft_isalnum(lex->c) || lex->c == '_')
			dynamic_string2(&var, lex->src[lex->i]);
		if (!ft_isalnum(lexer_gnc(lex)))
			break ;
		lexer_advance(lex);
	}
	return (var);
}

char	*slashify_in_quotes(char *line)
{
	char	*slashify;
	int		i;

	i = 0;
	if (!line)
		return (NULL);
	slashify = NULL;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'' )
			dynamic_string2(&slashify, '\\');
		dynamic_string2(&slashify, line[i]);
		i++;
	}
	return (slashify);
}

void	expand_dollar(t_lexer	*lex, char **string, t_bash *sh)
{
	char		*variable;
	char		*value;
	char		*temp;
	char		*temp2;

	variable = collect_variable(lex);
	value = search_string_env(variable, sh);
	value = slashify_in_quotes(value);
	temp2 = value;
	ft_memdel((void **)&variable);
	temp = *string;
	*string = parser_strjoin(*string, value);
	ft_memdel((void **)&value);
	free(temp);
}

void	parse_dollar(t_lexer	*lex, char **string, t_bash *sh)
{
	char	*dstring;

	if ((lexer_gnc(lex) != '_' && lexer_gnc(lex) != '?'
			&& !ft_isalnum(lexer_gnc(lex))) || lexer_gnc(lex) == '\0')
	{
		dynamic_string2(string, lex->src[lex->i]);
		return ;
	}
	if (lexer_gnc(lex) == '?')
	{
		dstring = ft_itoa(sh->exit_code);
		*string = wrapper_strjoin2(*string, dstring);
		lexer_advance(lex);
		return ;
	}
	lexer_advance(lex);
	expand_dollar(lex, string, sh);
}
