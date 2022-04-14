/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:07 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:22:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ftprintenv(t_bash **bash)
{
	dl_lstiter((*bash)->env, sfprint);
}

int	w_srchenv(void *t1, void *s2)
{
	t_env	*env;
	char	*str;

	str = NULL;
	env = t1;
	str = env->var;
	if (!env)
		return (-100);
	return (!ft_strcmp((char *)str, (char *)s2));
}

void	get_path(t_bash **bash)
{
	t_dllnode	*thenode;
	t_env		*env;
	t_dllnode	*temp_env;

	thenode = NULL;
	env = NULL;
	temp_env = (*bash)->env;
	thenode = dl_search(temp_env, w_srchenv, "PATH");
	if (!thenode)
		return ;
	env = thenode->data;
	(*bash)->path = ft_split(env->value, ':');
}

void	env_get(t_bash **sh, char **env)
{
	int			i;
	t_dllnode	**envtemp;

	envtemp = &((*sh)->env);
	i = 0;
	while (env[i])
	{
		dl_lstaddbac(envtemp, envsmake(env[i]));
		i++;
	}
}

void	iter_on_cmd(t_bash *sh, t_lexer *lex)
{
	t_dllnode	*one_line;

	one_line = sh->pipe_line;
	(void)lex;
	while (one_line)
	{
		prpar_command(sh, one_line->data);
		one_line = one_line->next;
	}
}
