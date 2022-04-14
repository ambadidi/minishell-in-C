/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:42:36 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:42:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		compstr;
	size_t		compfind;
	char		*str;
	char		*to_find;

	str = (char *)haystack;
	to_find = (char *)needle;
	compstr = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[compstr] != '\0' && compstr < len)
	{
		compfind = 0;
		while (to_find[compfind] == str[compstr + compfind]
			&& compstr + compfind < len)
		{
			if (to_find[compfind + 1] == '\0')
			{
				return (str + compstr);
			}
			compfind++;
		}
		compstr++;
	}
	return (0);
}
