/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:25:16 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 19:11:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_argc(char **argv)
{
	int		i;

	i = 0;
	if (argv == NULL)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

void	update_env_pwd(char *oldpwd, char *newpwd)
{
	t_dllnode		*node;
	t_bash			*bash;

	bash = get_bash__ptr(NULL);
	node = dl_search(bash->env, w_srchenv, "PWD");
	if (node)
		dl_del(&(bash->env), node, env_free);
	dl_lstaddbac(&(bash->env), env_new("PWD", newpwd));
	node = dl_search(bash->env, w_srchenv, "OLDPWD");
	if (node)
		dl_del(&(bash->env), node, env_free);
	dl_lstaddbac(&(bash->env), env_new("OLDPWD", oldpwd));
}

int	wrapper_chdir(char *path)
{
	int		ret;
	char	*old_pwd;
	char	*new_pwd;
	char	*test_path;

	old_pwd = getcwd(NULL, 0);
	ret = chdir(path);
	test_path = getcwd(NULL, 0);
	if (test_path == NULL)
	{
		ft_memdel((void **)&old_pwd);
		perror("cd");
		return (1);
	}
	ft_memdel((void **)&test_path);
	new_pwd = getcwd(NULL, 0);
	if (ret == -1)
		return (function_a(&old_pwd, &new_pwd));
	else
	{
		update_env_pwd(old_pwd, new_pwd);
		ft_memdel((void **)&old_pwd);
		ft_memdel((void **)&new_pwd);
		return (0);
	}
}

int	return_norm(int i)
{
	if (i == 42)
	{
		ft_putendl_fd("HOME not seted in this minishell", 2);
		return (1);
	}
	if (i == 1337)
	{
		ft_putendl_fd("too many argumnets cd Builtin Error", 2);
		return (1);
	}
	return (1);
}

int	builtin_cd(char **args, char	**env)
{
	char		*home;
	t_dllnode	*node;
	t_bash		*bash;

	(void)env;
	bash = get_bash__ptr(NULL);
	node = dl_search(bash->env, w_srchenv, "HOME");
	if (node == NULL)
		home = getenv("HOME");
	else
		home = ((t_env *)node->data)->value;
	if (get_argc(args) == 1)
	{
		if (home == NULL)
			return (return_norm(42));
		return (wrapper_chdir(home));
	}
	if (get_argc(args) == 2)
		return (wrapper_chdir(args[1]));
	else
		return (return_norm(1337));
}
