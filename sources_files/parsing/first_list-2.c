/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_list-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:21:22 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 16:25:40 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*char_join(char *first_str, int *i)
{
	int		j;
	int		space;
	char	*str;
	char	*new_str;

	j = *i;
	space = 0;
	while (_char(g_data->input[j], g_data->input[j - 1]) && g_data->input[j])
		j++;
	if (g_data->input[j] == ' ')
		space = 1;
	str = malloc(sizeof(char) * (j - *i + 1));
	j = 0;
	while (_char(g_data->input[*i], g_data->input[(*i) - 1])
		&& g_data->input[*i])
		str[j++] = g_data->input[((*i)++)];
	if (space)
		while (g_data->input[*i] == ' ')
			(*i)++;
	str[j] = '\0';
	new_str = ft_strjoin(first_str, str);
	free(str);
	return (new_str);
}

char	*quote_join(char *first_str, int *i)
{
	int		j;
	int		space;
	char	*str;
	char	type;
	char	*new_str;

	type = g_data->input[*i];
	(*i)++;
	j = *i;
	space = 0;
	while (g_data->input[j] != type && g_data->input[j - 1] != '\\')
		j++;
	if (g_data->input[j + 1] == ' ')
		space = 1;
	str = malloc(sizeof(char) * (j - *i + 1));
	copy_quote_str(str, i, type, space);
	new_str = ft_strjoin(first_str, str);
	if (_quote(g_data->input[(*i) - 1], g_data->input[(*i) - 2])
		&& g_data->input[(*i)])
		new_str = quote_join(new_str, i);
	else if (_char(g_data->input[(*i) - 1], g_data->input[(*i) - 2])
		&& g_data->input[(*i)])
		new_str = char_join(new_str, i);
	free(str);
	return (new_str);
}

char	*join_str(char *first_str, int *i)
{
	if (_quote(g_data->input[*i], g_data->input[*i - 1]))
		first_str = quote_join(first_str, i);
	else if (_char(g_data->input[*i], g_data->input[*i - 1]))
		first_str = char_join(first_str, i);
	return (first_str);
}

void	copy_quote_str(char *str, int *i, char type, int space)
{
	int	j;

	j = 0;
	while (g_data->input[*i])
	{
		if (g_data->input[*i] == type && g_data->input[*i - 1] != '\\')
			break ;
		str[j++] = g_data->input[((*i)++)];
	}
	if (space)
	{
		(*i)++;
		while (g_data->input[*i] == ' ')
			(*i)++;
	}
	else
		(*i)++;
	str[j] = '\0';
}

int	count_quote_str(int j, char type)
{
	while (g_data->input[j])
	{
		if (g_data->input[j] == type && g_data->input[j - 1] != '\\')
			break ;
		j++;
	}
	return (j);
}
