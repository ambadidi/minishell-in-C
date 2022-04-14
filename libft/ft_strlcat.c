/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:41:56 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:41:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lens;
	size_t	lend;
	size_t	j;

	i = 0;
	lend = 0;
	lens = 0;
	while (dest[lend])
		lend++;
	while (src[lens])
		lens++;
	j = lend;
	if (size > j)
	{
		while (src[i] != '\0' && i < size - j - 1)
		{
			dest[j + i] = src[i];
			i++;
		}
		dest[i + j] = '\0';
	}
	else if (size <= j)
		return (size + lens);
	return (lens + lend);
}
