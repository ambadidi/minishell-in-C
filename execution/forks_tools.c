/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:30:01 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:30:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	isadirectory(char *path)
{
	if (!path)
		return (FALSE);
	if (ft_strchr(path, '/'))
		return (TRUE);
	return (FALSE);
}

int	is_exist(char *path)
{
	int		d;

	d = open(path, O_RDONLY);
	if (d < 0)
		return (0);
	close(d);
	return (1);
}

char	*get_path_cmd(char *str, char **path)
{
	char	*fullpath;
	int		i;
	char	*tmpf;

	i = 0;
	fullpath = NULL;
	tmpf = NULL;
	if (path == NULL)
		return (NULL);
	while (path[i])
	{
		fullpath = ft_strjoin(path[i], "/");
		tmpf = fullpath;
		fullpath = ft_strjoin(fullpath, str);
		if (is_exist(fullpath) == 1)
		{
			ft_memdel((void **) &tmpf);
			return (fullpath);
		}
		ft_memdel((void **) &tmpf);
		ft_memdel((void **) &fullpath);
		i++;
	}
	return (NULL);
}

t_bool	isredirection(t_cmdtable	*cmd)
{
	if (cmd->files)
		return (TRUE);
	return (FALSE);
}

void	execution_error(int exit_code)
{
	perror("minishell");
	if (errno == 13)
		exit (126);
	exit(exit_code);
}
