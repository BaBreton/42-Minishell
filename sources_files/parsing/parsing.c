/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:50:38 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 11:25:40 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_backslash(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\\'
			&& ((_spec(str[i + 1], '\0')) || (_quote(str[i + 1], '\0'))))
			i++;
		j++;
	}
	return (j);
}

char	*remove_backslash(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	j = count_backslash(str);
	tmp = malloc(sizeof(char) * (j + 1));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '\\'
			&& ((_spec(str[i + 1], '\0')) || (_quote(str[i + 1], '\0'))
				|| str[i + 1] == '\\'))
			i++;
		tmp[j++] = str[i];
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\'
			&& ((_spec(str[i + 1], '\0')) || (_quote(str[i + 1], '\0'))
				|| str[i + 1] == '\\'))
			return (1);
		i++;
	}
	return (0);
}

void	format_first_list(void)
{
	t_qlist	*tmp;

	tmp = g_data->q_list;
	while (tmp)
	{
		if (check_backslash(tmp->str))
			tmp->str = remove_backslash(tmp->str);
		if (tmp->type == 0 || tmp->type == 2)
			tmp->str = dollar_check(tmp->str);
		tmp = tmp->next;
	}
}

void	parsing_input(void)
{
	g_data->input = ft_strtrim(g_data->input, " ");
	g_data->input = add_first_char();
	first_list();
	format_first_list();
	second_list();
	qlist_clear(&g_data->q_list);
}
