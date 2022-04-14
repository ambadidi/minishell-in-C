/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:37 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 20:06:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*firstsplit(char const *s, unsigned int start, char c)
{
	char		*str;
	size_t		i;
	size_t		len;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (s[len] != c && s[len])
		len++;
	i = 0;
	str = malloc((len + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = 0;
	return (str);
}

t_bool	is_backslashisatend(char *str)
{
	int		i;
	int		size;

	size = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == size - 1)
		return (TRUE);
	return (FALSE);
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;
	char	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	new->var = nulled_strdup(key);
	new->value = nulled_strdup(value);
	tmp = ft_strjoin(new->var, "=");
	new->cmd = ft_strjoin(tmp, new->value);
	ft_memdel((void **)&tmp);
	return (new);
}

t_env	*envsmake(char *env)
{
	t_env	*s;
	char	*tmp;

	s = malloc(sizeof(t_env));
	s->cmd = ft_strdup(env);
	ft_strchr(env, '=');
	s->var = firstsplit(env, 0, '=');
	if (!ft_strchr(env, '='))
	{
		s->var = ft_strdup(env);
		s->value = ft_strdup("");
		return (s);
	}
	if (is_backslashisatend(env) == TRUE)
		s->value = ft_strdup("");
	else
	{
		tmp = ft_strchr(env, '=');
		++tmp;
		if (*tmp == '\0')
			s->value = ft_strdup("");
		else
			s->value = ft_strdup(tmp);
	}
	return (s);
}

void	sfprint(void *c)
{
	printf("\ncmd : |%s|\n", ((t_env *)c)->cmd);
	printf("var : |%s|\n", ((t_env *)c)->var);
	printf("value : |%s|\n", ((t_env *)c)->value);
}
