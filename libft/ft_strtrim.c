/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:42:54 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static	int	ssss(char const *seti, char c)
{
	while (*seti)
	{
		if (*seti == c)
			return (1);
		seti++;
	}
	return (0);
}

static	int	is_existw(char const *str, char const *set)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ssss(set, str[i]) == 1)
			i++;
		else
			return (i);
	}
	return (0);
}

static	int	is_existl(char const *str, char const *set, int len)
{
	int		i;

	i = len - 1;
	while (i >= 0)
	{
		if (ssss(set, str[i]) == 1)
			i--;
		else
			return (i);
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lend;
	int		fx;
	int		lx;
	char	*c;

	if (!s1)
		return (NULL);
	fx = is_existw(s1, set);
	lend = ft_strlen(s1);
	lx = is_existl(s1, set, lend);
	if (lx == lend)
	{
		c = malloc(sizeof(char));
		c[0] = '\0';
		return (c);
	}
	c = ft_substr(s1, fx, lx - fx + 1);
	return (c);
}
