/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:48:24 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:17:05 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	isclose(char *str)
{
	int		i;
	char	f;

	i = 0;
	f = 0;
	while (str[i])
	{
		if (str[i] == '"' && str[i] != f && f != '\'')
			f = str[i];
		else if (str[i] == '\'' && str[i] != f && f != '"')
			f = str[i];
		else if (str[i] == '"' && f == str[i])
			f = 0;
		else if (str[i] == '\'' && f == str[i])
			f = 0;
		i++;
	}
	if (f)
		return (FALSE);
	return (FAILURE);
}

t_status	precompilation(char *line, t_bash *bash)
{
	t_lexer		*lex;

	lex = lexer_init(line);
	lexer_start(lex, bash);
	if (check_syntax(bash) == FAILURE)
	{
		dl_clear(&(bash->tokken), tokken_free);
		lexer_free(&lex);
		bash->exit_code = 258;
		return (FAILURE);
	}
	lexer_free(&lex);
	dl_clear(&(bash->tokken), tokken_free);
	return (SUCCES);
}

t_status	compile_line(char *line, t_bash *bash)
{
	t_lexer	*lex;

	if (!isclose(line))
	{
		ft_putstr_fd("bash: syntax error - open quotes \n", 2);
		return (FAILURE);
	}
	if (precompilation(line, bash) == FAILURE)
		return (lex_errors(bash));
	lex = lexer_init(line);
	bash->env_array = point_to_env(bash->env);
	get_path(&bash);
	pipe_split(lex, bash);
	lexer_free(&lex);
	iter_on_cmd(bash, lex);
	execute_on_cmd(bash);
	dl_clear(&(bash->pipe_line), free);
	return (SUCCES);
}
