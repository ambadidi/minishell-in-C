/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linkedlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:34:01 by marvin           #+#    #+#             */
/*   Updated: 2022/04/14 22:32:11 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extralibft.h"

t_dllnode	*dl_lstnew(void *content)
{
	t_dllnode	*head;

	head = malloc(sizeof(t_dllnode));
	if (!head)
		return (NULL);
	head->data = content;
	head->next = NULL;
	head->prev = NULL;
	return (head);
}

void	dl_lstaddfro(t_dllnode **head, void *content)
{
	t_dllnode	*temp;
	t_dllnode	*node;

	temp = *head;
	node = dl_lstnew(content);
	*head = node;
	node->next = temp;
	temp->prev = node;
}

void	dl_lstaddbac(t_dllnode **head, void *content)
{
	t_dllnode	*temp;
	t_dllnode	*i;

	i = *head;
	if (*head == NULL)
	{
		*head = dl_lstnew(content);
	}
	else
	{
		while (i)
		{
			if (!i->next)
			{
				temp = dl_lstnew(content);
				temp->prev = i;
				i->next = temp;
				break ;
			}
			i = i->next;
		}
	}
}

void	dl_lstiter(t_dllnode *head, void (*f)(void *))
{
	t_dllnode	*i;

	if (!(head) || !(f))
		return ;
	i = head;
	while (i)
	{
		f(i->data);
		i = i->next;
	}
}

void	dl_delone(t_dllnode *node, void (*f)(void *))
{
	if (node != NULL && f != NULL)
	{
		f((node)->data);
		free(node);
	}
}
