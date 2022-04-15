/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:39:47 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;
	char	*s;
	char	*d;

	d = (char *)dst;
	s = (char *)src;
	if (d == NULL && s == NULL)
		return (NULL);
	if (len == 0)
		return (d);
	if (src < dst)
	{
		i = (int)len;
		while (--i >= 0)
			d[i] = s[i];
	}
	else
	{
		i = -1;
		while (++i < (int)len)
			d[i] = s[i];
	}
	return (d);
}
