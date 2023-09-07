/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q-list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 22:49:30 by babreton          #+#    #+#             */
/*   Updated: 2023/07/09 22:50:06 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_qlist	*qlist_new(char *str, int type)
{
	t_qlist	*new;

	new = malloc(sizeof(t_qlist));
	new->str = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	return (new);
}

t_qlist	*qlist_last(t_qlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	qlist_add_back(t_qlist **lst, t_qlist *new)
{
	t_qlist	*last;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = qlist_last(*lst);
	last->next = new;
}

void	qlist_clear(t_qlist **lst)
{
	t_qlist	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str);
		free(*lst);
		*lst = tmp;
	}
}
