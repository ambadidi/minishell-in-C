/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:45:44 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "extralibft.h"

void	stringlst(t_dllnode **head, char *str)
{
	int		i;

	head = NULL;
	i = 0;
	while (str[i])
	{
		dl_lstaddbac(head, ft_strdup(&str[i]));
		i++;
	}
}

int	sizeoflst(t_dllnode *head)
{
	int		i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	*lststring(t_dllnode *head)
{
	int			i;
	char		*t;
	char		*str;

	i = 0;
	str = malloc((sizeoflst(head) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (!sizeoflst(head))
		return (NULL);
	while (head)
	{
		t = head->data;
		str[i] = t[0];
		head = head->next;
		i++;
	}
	str[i] = '\0';
	return (str);
}
