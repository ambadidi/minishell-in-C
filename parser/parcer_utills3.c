/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utills3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:00 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:22:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_args(t_dllnode *parsed)
{
	t_tokken	*temp;
	char		*string;

	string = NULL;
	while (parsed)
	{
		temp = parsed->data;
		if (temp->type == O_WORD)
		{
			string = wrapper_strjoin(string, " ");
			string = wrapper_strjoin(string, temp->content);
		}
		parsed = parsed->next;
	}
	return (string);
}

t_dllnode	*wraper_get_redirection(t_bash *sh, char *line, char **remainline)
{
	t_lexer		*lexer;
	t_dllnode	*parsed;
	t_dllnode	*redirection;

	redirection = NULL;
	lexer = lexer_init(line);
	parsed = cmd_tokken_start(lexer, sh);
	specify_redirection(parsed);
	redirection = extract_redirections(parsed);
	*remainline = extract_args(parsed);
	dl_clear(&parsed, tokken_free);
	lexer_free(&lexer);
	return (redirection);
}
