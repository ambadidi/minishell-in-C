/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:42 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:47:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parser_strjoin(char *s1, char *s2)
{
	int		lens1;
	int		lens2;
	char	*str;
	int		i;

	i = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	str = (char *)malloc((lens1 + lens2) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (i < lens1)
	{
		str[i] = s1[i];
		i++;
	}
	i = -1;
	while (++i < lens2)
	{
		str[i + lens1] = s2[i];
	}
	str[lens1 + i] = '\0';
	return (str);
}

void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

char	*wrapper_strjoin(char *line, char *line2)
{
	char	*shit;

	shit = parser_strjoin(line, line2);
	free(line);
	return (shit);
}

char	*wrapper_strjoin2(char *line, char *line2)
{
	char	*shit;

	shit = parser_strjoin(line, line2);
	if (line)
		free(line);
	if (line2)
		free(line2);
	return (shit);
}
