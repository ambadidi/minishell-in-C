/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:41:19 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:41:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static	int	ft_wc(char *str, char c)
{
	int		state;
	int		wc;

	state = 0;
	wc = 0;
	while (*str)
	{
		if (*str == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			++wc;
		}
		++str;
	}
	return (wc);
}

static	char	*ft_extractor(char *s, char c)
{
	int		i;
	char	*d;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	d = ft_substr(s, 0, i);
	if (d == NULL)
		return (NULL);
	return (d);
}

static	void	garbage_collec(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

static int	boucle(char **tab, const char *s, int *i, char c)
{
	int		j;

	j = -1;
	while (s[++(j)])
	{
		if (!(s[j] == c && s[j]))
		{
			tab[*i] = ft_extractor((char *)s + j, c);
			if (tab[*i] == NULL)
			{
				garbage_collec(tab, *i);
				return (0);
			}
			(*i)++;
			while (s[j + 1] != c && s[j + 1])
				j++;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		wc;

	if (s == NULL)
		return (NULL);
	wc = ft_wc((char *)s, c);
	tab = (char **)malloc((wc + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	i = 0;
	if (boucle(tab, s, &i, c) == 0)
		return (NULL);
	tab[i] = NULL;
	return (tab);
}
