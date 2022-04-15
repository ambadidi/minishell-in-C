/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extralibft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:34:21 by marvin            #+#    #+#             */
/*   Updated: 2022/04/14 22:32:53 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRALIBFT_H
# define EXTRALIBFT_H
# include "libft.h"
# include "limits.h"
# include <sys/types.h>
# include <dirent.h>

/*
** colors
*/
# define PATHS_MAX	4096
# define KNRM		"\x1B[0m"
# define KRED		"\x1B[31m"
# define KGRN		"\x1B[32m"
# define KYEL		"\x1B[33m"
# define KBLU		"\x1B[34m"
# define KMAG		"\x1B[35m"
# define KCYN		"\x1B[36m"
# define KWHT		"\x1B[37m"

/*
**	Double linked list
*/
typedef struct s_dllnode
{
	void				*data;
	struct s_dllnode	*next;
	struct s_dllnode	*prev;
}					t_dllnode;
/*
** DLL FUNCTIONS
*/
t_dllnode			*dl_lstnew(void *content);
void				dl_lstaddfro(t_dllnode **head, void *content);
void				dl_lstaddbac(t_dllnode **head, void *content);
void				dl_lstiter(t_dllnode *head, void (*f)(void *));
void				dl_delone(t_dllnode *node, void (*f)(void *));
void				dl_clear(t_dllnode **node, void (*f)(void *));
void				dl_del(t_dllnode **head, t_dllnode *node,
						void (*f)(void *));
void				*dl_search(t_dllnode *head, int (*f)(void*, void*),
						void *tofind);

void				stringlst(t_dllnode **head, char *str);
int					sizeoflst(t_dllnode *head);
char				*lststring(t_dllnode *head);

#endif
