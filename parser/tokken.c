/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokken.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:48:09 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:17:21 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_tokken	*tokken_init(char *content, t_ops op)
{
	t_tokken	*tokken;

	tokken = malloc (sizeof(t_tokken));
	if (!tokken)
		return (NULL);
	tokken->content = ft_strdup(content);
	tokken->type = op;
	return (tokken);
}

void	tokken_free(void	*tok)
{
	t_tokken	*t;

	t = tok;
	free(t->content);
	t->type = O_NONE;
	free(tok);
}
