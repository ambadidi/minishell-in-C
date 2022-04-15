/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linkedlist_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:48 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extralibft.h"

void	dl_clear(t_dllnode **node, void (*f)(void *))
{
	t_dllnode	*temp;
	t_dllnode	*i;

	if (!(node) || !(*node) || !(f))
		return ;
	i = *node;
	if (*node != NULL && f != NULL)
	{
		while (i)
		{
			temp = (i)->next;
			dl_delone(i, f);
			i = temp;
		}
		*node = NULL;
	}
}

void	*dl_search(t_dllnode *head, int (*f)(void*, void*),
					void *tofind)
{
	t_dllnode	*t;
	t_dllnode	*find;

	find = NULL;
	t = head;
	while (t)
	{
		if (f(t->data, tofind))
		{
			find = t;
			break ;
		}
		t = t->next;
	}
	return (find);
}

void	dl_del(t_dllnode **head, t_dllnode *node, void (*f)(void *))
{
	t_dllnode	*tmp;
	t_dllnode	*current;
	t_dllnode	*prev;
	t_dllnode	*next;

	if (node->prev)
	{
		tmp = node;
		current = node;
		prev = node->prev;
		next = node->next;
		prev->next = next;
		if (next)
			next->prev = prev;
		dl_delone(tmp, f);
	}
	else
	{
		tmp = node;
		*head = node->next;
		dl_delone(tmp, f);
	}
}
