/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:46:52 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:21:30 by marvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	files_destruct(void *files)
{
	t_files		*temp;

	temp = files;
	if (temp->path)
	{
		unlink(temp->path);
		free(temp->path);
		temp->path = NULL;
	}
	if (temp->value)
	{
		free(temp->value);
		temp->value = NULL;
	}
	free(temp);
}

t_files	*files_constr(t_ops type, char *value)
{
	t_files		*file;

	file = malloc(sizeof(t_files));
	if (!file)
		return (NULL);
	if (type == F_HEREDOC)
		file->isheredoc = TRUE;
	else
		file->isheredoc = FALSE;
	file->type = type;
	file->value = ft_strdup(value);
	file->path = NULL;
	return (file);
}
