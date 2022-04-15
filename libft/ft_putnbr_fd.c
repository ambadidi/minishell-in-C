/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:40:54 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pputchar(int fd, char c)
{
	write(fd, &c, 1);
}

void	ft_pputnbr(int fd, int nb)
{
	long	i;

	i = nb;
	if (i < 0)
	{
		ft_pputchar(fd, '-');
		i = i * (-1);
	}
	if (i > 9)
	{
		ft_pputnbr(fd, i / 10);
		ft_pputnbr(fd, i % 10);
	}
	else
	{
		ft_pputchar(fd, i + '0');
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_pputnbr(fd, n);
}
