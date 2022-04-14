/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utills.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:26:44 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 18:26:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_bool	if_var_valid(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	if_prefix_valid(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isalpha(cmd[i]) || cmd[i] == '_')
		return (TRUE);
	return (FALSE);
}

void	copy_and_delete(char **dest, char *new_value)
{
	char	*tmp;

	tmp = NULL;
	if (*dest)
	{
		tmp = *dest;
		*dest = ft_strdup(new_value);
		ft_memdel((void **)&tmp);
	}
}

int	export_var(char *cmd, t_bash *sh)
{
	t_env		*env;
	int			state;

	state = 0;
	env = envsmake(cmd);
	if (!if_var_valid(env->var) || !if_prefix_valid(env->var))
	{
		ft_putendl_fd("export: invalid argument", 2);
		state = 1;
	}
	else if (!if_env_exist_and_update(env, sh))
	{
		if (!ft_strchr(env->cmd, '='))
			dl_lstaddbac(&(sh->env_useless), envsmake(cmd));
		if (ft_strchr(env->cmd, '='))
			dl_lstaddbac(&(sh->env), envsmake(cmd));
	}
	env_free(env);
	return (state);
}

int	loop_on_env(char **args, t_bash *bash)
{
	int		i;
	int		state;
	int		ret;

	i = 1;
	state = 0;
	ret = 0;
	while (args[i])
	{
		state = export_var(args[i], bash);
		if (state == 1 && ret == 0)
			ret = 1;
		i++;
	}
	return (ret);
}
