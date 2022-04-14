/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:48:33 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:48:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdarg.h>

t_bash	*get_bash__ptr(t_bash *bash)
{
	static t_bash	*ptr = NULL;

	if (bash)
		ptr = bash;
	return (ptr);
}

t_bash	*bash_init(void)
{
	t_bash		*bash;

	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (NULL);
	bash->env = NULL;
	bash->env_array = NULL;
	bash->tokken = NULL;
	bash->path = NULL;
	bash->pipe_line = NULL;
	bash->cmds_list = NULL;
	bash->env_useless = NULL;
	bash->exit_code = 0;
	bash->index = 0;
	get_bash__ptr(bash);
	return (bash);
}

void	string_array_free(char **array)
{
	int		i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	bash_cleaning(t_bash **bash)
{
	t_bash		*sh;

	sh = *bash;
	dl_clear(&(sh->tokken), tokken_free);
	dl_clear(&(sh->pipe_line), free);
	dl_clear(&(sh->cmds_list), cmd_list_destruct);
	if (sh->env_array)
	{
		free(sh->env_array);
		sh->env_array = NULL;
	}
	string_array_free(sh->path);
	sh->path = NULL;
	(*bash)->index = 0;
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_bash		*bash;

	bash = bash_init();
	(void)(argc);
	(void)(argv);
	env_get(&bash, env);
	g_pid = 0;
	signal(SIGINT, signal_handler_sigint);
	signal(SIGQUIT, signal_handler_sigquit);
	while (1)
	{	
		line = readline("$minsihell> ");
		if (line == NULL)
			exit(0);
		add_history(line);
		if (line[0] != '\0')
		{
			if (compile_line(line, bash) == FAILURE)
				bash_cleaning(&bash);
			bash_cleaning(&bash);
			free(line);
		}
	}
	return (0);
}
