/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:44:26 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:44:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	bg_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*bg_strdup(const char *s)
{
	size_t	k;
	char	*new;
	size_t	i;

	i = 0;
	k = 0;
	while (s[k] != '\0')
		k++;
	new = (char *)malloc((k + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*bg_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (0);
	if (start > bg_strlen(s))
		len = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (start < bg_strlen(s))
	{
		while (i < len && s[start])
		{
			str[i] = s[start];
			i++;
			start++;
		}
		str[i] = '\0';
	}
	else
		str[i] = '\0';
	return (str);
}

char	*bg_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(bg_strlen(s1) + bg_strlen(s2) + 1);
	if (!str)
		return (NULL);
	while (*s1)
	{
		str[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*bg_strchr(const char *s, int c)
{
	int		i;
	char	str;

	str = (unsigned char)c;
	i = 0;
	while (s[i] != str)
	{
		if (s[i] == '\0')
			return (0);
		i++;
	}
	return ((char *)s + i);
}
