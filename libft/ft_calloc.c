/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:35:10 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:35:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t c, size_t size)
{
	size_t	s;
	void	*p;

	s = c * size;
	p = malloc(s);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, s);
	return (p);
}
