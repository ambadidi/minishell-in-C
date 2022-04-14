/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linkedlist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:34:01 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:34:06 by marvin           ###   ########.fr       */
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

/*
** to add a node in the begining of the list
** we use addfront
*/

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

/*
** to add a node in the end of the list
** we use addback
*/

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

/*
** Iterates the list ’lst’ and applies the function
** ’f’ to the content of each element.
*/

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

/*
**	Takes as a parameter an element and frees the
** memory of the element’s content using the function
** ’del’ given as a parameter and free the element.
** The memory of ’next’ must not be freed.
*/

void	dl_delone(t_dllnode *node, void (*f)(void *))
{
	if (node != NULL && f != NULL)
	{
		f((node)->data);
		free(node);
	}
}
