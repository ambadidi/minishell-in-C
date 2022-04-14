/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:34:51 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:34:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ternary_atoi(long x, long y, long ifeq, long ifneq)
{
	if (x == y)
		return (ifeq);
	else
		return (ifneq);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	num;
	int		neg;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	neg = ternary_atoi(str[i], '-', -1, 1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0')
	{
		if (num <= ((MAX_ATOI - (str[i] - 48)) / 10))
			num = num * 10 + (str[i] - 48);
		else
		{
			num = ternary_atoi(neg, -1, 0, -1);
			break ;
		}
		i++;
	}
	return (num * neg);
}
