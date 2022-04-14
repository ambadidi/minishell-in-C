/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:30:32 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:30:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_error(char *str, char *str2, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	error_management(char *path)
{
	struct stat	buf;
	int			errno__;

	errno__ = errno;
	errno = 0;
	stat(path, &buf);
	if (errno != 0)
		execution_error(127);
	if (S_ISDIR(buf.st_mode))
		print_error(": is a directory", path, 126);
	errno = errno__;
}

void	handle_execution_builin(char **argv, char **env)
{
	exit(builtin_execution(argv, env));
}

t_bool	if_spaces(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{	
		if (str[i] == ' ')
			if (isnotquoted(str, i, '"') == TRUE
				&& isnotquoted(str, i, '\'') == TRUE)
				return (TRUE);
		i++;
	}
	return (FALSE);
}

int	child_open_fd(char *path, int flags)
{
	int		fd;
	char	*cmd;

	if (lets_try_expand(path, &cmd) == TRUE)
		path = cmd;
	fd = open(path, flags, S_IRUSR | S_IWUSR);
	if (fd < 0)
		execution_error(1);
	ft_memdel((void **) &cmd);
	return (fd);
}
