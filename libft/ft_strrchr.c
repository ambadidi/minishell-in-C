/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:42:43 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:42:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*ss;

	ss = (char *)s;
	len = 0;
	while (ss[len])
		len++;
	while (len >= 0)
	{
		if (ss[len] == c)
		{
			return (ss + len);
		}
		len--;
	}
	return (NULL);
}
