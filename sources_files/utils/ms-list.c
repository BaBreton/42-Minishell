/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms-list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:29:19 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 17:29:38 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ms	*ms_new(char **content, int type, int size)
{
	t_ms	*list;

	list = (t_ms *)malloc(sizeof(t_ms));
	list->words = double_chardup(content, size);
	list->type = type;
	if (type == 1)
	{
		if (content[0][0] == '|')
			list->type = 1;
		else if (content[0][0] == '<' && content[0][1] != '<')
			list->type = 2;
		else if (content[0][0] == '>' && content[0][1] != '>')
			list->type = 3;
		else if (content[0][0] == '>' && content[0][1] == '>')
			list->type = 4;
		else if (content[0][0] == '<' && content[0][1] == '<')
			list->type = 5;
		else if (content[0][0] == ';')
			list->type = 6;
		else if (content[0][0] == '&')
			list->type = 7;
	}
	list->size = size;
	list->next = NULL;
	return (list);
}

t_ms	*ms_last(t_ms *lst)
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

void	ms_back(t_ms **lst, t_ms *new)
{
	t_ms	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ms_last(*lst);
	last->next = new;
}

void	ms_clear(t_ms **lst)
{
	t_ms	*tmp;
	int		i;

	i = -1;
	if (!lst)
		return ;
	while (*lst)
	{
		i = -1;
		tmp = *lst;
		while (++i < (*lst)->size)
			free((*lst)->words[i]);
		free((*lst)->words);
		*lst = (*lst)->next;
		free(tmp);
	}
	*lst = NULL;
}
