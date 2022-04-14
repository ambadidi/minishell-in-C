/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:31:27 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:11:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_hd_filepath(char *str, int i)
{
	char	*path;
	char	*number;

	number = ft_itoa(i);
	path = ft_strjoin(str, number);
	free(number);
	return (path);
}

int	fd_here_doc_create(t_files *files, t_bash *bash)
{
	int		fd;
	char	*path;

	path = get_hd_filepath("/tmp/file", bash->index);
	fd = open(path, O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	files->path = ft_strdup(path);
	free(path);
	return (fd);
}

void	heredoc_write_read(int fd, t_files *files, t_bash *bash)
{
	char	*line_;
	char	*stopvalue;

	(void)bash;
	stopvalue = files->value;
	while (1)
	{
		line_ = readline("heredoc>");
		if (!line_)
			break ;
		if (strcmp(line_, stopvalue) == 0)
			break ;
		write(fd, line_, ft_strlen(line_));
		write(fd, "\n", 1);
		free(line_);
		line_ = NULL;
	}
	if (line_)
		free(line_);
	bash->index++;
	close(fd);
}

void	herdoc_checker(t_dllnode *files, t_bash *bash)
{
	t_files		*file;

	while (files)
	{
		file = files->data;
		if (file->isheredoc == TRUE)
			heredoc_write_read(fd_here_doc_create(file, bash), file, bash);
		files = files->next;
	}
}

void	here_doc_init(t_bash *sh)
{
	t_dllnode	*node;
	t_cmdtable	*cmd;

	node = sh->cmds_list;
	while (node)
	{
		cmd = node->data;
		herdoc_checker(cmd->files, sh);
		node = node->next;
	}
}
//export b="ls -la"toto'tata'