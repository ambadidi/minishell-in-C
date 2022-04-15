/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:37:31 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_bbzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	rev(char *str, int i, long d)
{
	while (d > 0)
	{
		str[i] = d % 10 + 48;
		d /= 10;
		i--;
	}
}

int	ft_count(int n)
{
	int		digits;
	long	number;

	if (n == 0)
		return (1);
	digits = 0;
	number = n;
	while (number != 0)
	{
		number /= 10;
		digits++;
	}
	if (n < 0)
		digits += 1;
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	d;
	int		l;

	i = 0;
	d = n;
	l = ft_count(n) + 1;
	str = (char *)malloc(l * sizeof(char));
	if (!str)
		return (NULL);
	ft_bbzero(str, l);
	if (n < 0)
	{
		str[i] = '-';
		i++;
		d = d * -1;
	}
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	rev(str, ft_count(n) - 1, d);
	return (str);
}
