/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:29:03 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 17:30:17 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list_loop(char ***words, int *allocated, int *i, t_qlist *tmp)
{
	if (*allocated == 0)
	{
		*words = (char **)malloc(sizeof(char *));
		(*words)[0] = ft_strdup(tmp->str);
		*i = 1;
		*allocated = 1;
	}
	else
	{
		*words = str_to_tab(*words, tmp->str, (*i)++, 0);
	}
	if (tmp->next == NULL || tmp->next->type == 3)
	{
		*words = str_to_tab(*words, NULL, *i, 0);
		ms_back(&g_data->ms_list, ms_new(*words, 0, *i));
		free_char(*words, *i);
		*words = NULL;
		*allocated = 0;
	}
}

void	second_list(void)
{
	char	**words;
	int		allocated;
	int		i;
	t_qlist	*tmp;

	allocated = 0;
	words = NULL;
	tmp = g_data->q_list;
	while (tmp)
	{
		if (tmp->type != 3)
			print_list_loop(&words, &allocated, &i, tmp);
		else
		{
			words = (char **)malloc(sizeof(char *) * 2);
			words[0] = ft_strdup(tmp->str);
			words[1] = NULL;
			ms_back(&g_data->ms_list, ms_new(words, 1, 1));
			free_char(words, 2);
			words = NULL;
		}
		tmp = tmp->next;
	}
}
