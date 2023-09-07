/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:53:09 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 15:55:13 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_line_init(void)
{
	g_data->nl_error = 0;
	g_data->first_call = 0;
	g_data->q_list = NULL;
	g_data->ms_list = NULL;
	if (g_data->exit_status == 258)
		g_data->exit_status = 0;
}

void	quote_loop(int *i, int *quote, char *type)
{
	while (g_data->input[++(*i)])
	{
		if (_quote(g_data->input[*i], g_data->input[(*i) - 1]) && !(*type))
		{
			*type = g_data->input[*i];
			(*quote)++;
			(*i)++;
		}
		if (g_data->input[*i] == *type)
		{
			*quote = 0;
			*type = 0;
		}
	}
}

int	check_quote(void)
{
	int		i;
	int		quote;
	char	type;

	i = -1;
	quote = 0;
	type = 0;
	if (_quote(g_data->input[0], '\0'))
	{
		type = g_data->input[0];
		quote++;
	}
	i++;
	quote_loop(&i, &quote, &type);
	if (quote % 2 != 0)
	{
		g_data->nl_error = 1;
		return (printf("minishell: syntax error: quote error\n"));
	}
	return (0);
}

int	new_line_error(void)
{
	int	i;

	i = -1;
	if (g_data->input == NULL)
		return (g_data->nl_error = 1, 1);
	if (g_data->input[0] == '\0')
		return (g_data->nl_error = 1, 1);
	if (check_quote())
		return (g_data->nl_error = 2, 1);
	while (g_data->input[++i])
	{
		if (_char(g_data->input[i], '\0'))
			return (0);
		if (_space(g_data->input[i]))
		{
			while (_space(g_data->input[i]) && g_data->input[i])
				i++;
			if (g_data->input[i] == '\0')
				return (g_data->nl_error = 1, 1);
		}
	}
	return (0);
}

void	check_new_line(void)
{
	if (g_data->first_call == 0)
		ms_clear(&g_data->ms_list);
	new_line_init();
	if (new_line_error())
		return ;
}
