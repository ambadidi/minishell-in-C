/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:37:42 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*n;

	n = *alst;
	if (!new)
		return ;
	if (!*alst)
		(*alst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
}
