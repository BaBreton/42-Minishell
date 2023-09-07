/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_list-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:21:39 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 17:14:21 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quote_parser(int *i)
{
	int		j;
	int		space;
	char	*str;
	char	type;

	type = g_data->input[*i];
	(*i)++;
	j = *i;
	space = 0;
	j = count_quote_str(j, type);
	if (g_data->input[j + 1] == ' ')
		space = 1;
	str = malloc(sizeof(char) * (j - *i + 1));
	copy_quote_str(str, i, type, space);
	if (!_space(g_data->input[(*i) - 1]) && g_data->input[(*i)])
		str = join_str(str, i);
	if (type == '\'')
		qlist_add_back(&g_data->q_list, qlist_new(str, 1));
	else if (type == '\"')
		qlist_add_back(&g_data->q_list, qlist_new(str, 2));
	free(str);
}

void	spec_parser(int *i)
{
	int		j;
	int		space;
	char	*str;

	j = *i;
	space = 0;
	while (_spec(g_data->input[j], g_data->input[j - 1]))
		j++;
	if (g_data->input[j] == ' ')
		space = 1;
	str = malloc(sizeof(char) * (j - *i + 1));
	j = 0;
	while (_spec(g_data->input[*i], g_data->input[(*i) - 1]))
		str[j++] = g_data->input[((*i)++)];
	if (space)
		while (g_data->input[*i] == ' ')
			(*i)++;
	str[j] = '\0';
	qlist_add_back(&g_data->q_list, qlist_new(str, 3));
	free(str);
}

void	char_parser(int *i)
{
	int		j;
	int		space;
	char	*str;

	j = (*i);
	space = 0;
	while (_char(g_data->input[j], g_data->input[j - 1]))
		j++;
	if (g_data->input[j] == ' ')
		space = 1;
	str = malloc(sizeof(char) * (j - *i + 1));
	j = 0;
	while (_char(g_data->input[*i], g_data->input[(*i) - 1]))
		str[j++] = g_data->input[((*i)++)];
	if (space)
		while (g_data->input[*i] == ' ')
			(*i)++;
	str[j] = '\0';
	qlist_add_back(&g_data->q_list, qlist_new(str, 0));
	free(str);
}

void	first_list(void)
{
	int		i;

	i = 1;
	while (g_data->input[i])
	{
		if (_char(g_data->input[i], g_data->input[i - 1]))
			char_parser(&i);
		else if (_spec(g_data->input[i], g_data->input[i - 1]))
			spec_parser(&i);
		else if (_quote(g_data->input[i], g_data->input[i - 1]))
			quote_parser(&i);
		if (g_data->input[i] == '\0')
			break ;
	}
}
