/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:24:42 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	function_a(char **string_o, char **string__p)
{
	perror("cd");
	ft_memdel((void **)&(*string_o));
	ft_memdel((void **)&(*string__p));
	return (1);
}
