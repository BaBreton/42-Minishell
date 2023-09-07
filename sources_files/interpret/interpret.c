/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:48:10 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 15:51:36 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_syntax(void)
{
	t_ms	*tmp;

	tmp = g_data->ms_list;
	while (tmp)
	{
		if (tmp->type != 0 && tmp->next && tmp->next->type != 0)
		{
			printf("minishell: syntax error near unexpected token `");
			g_data->exit_status = 258;
			return (printf("%s'\n", tmp->next->words[0]), 1);
		}
		if (tmp->type != 0 && tmp->next == NULL)
		{
			printf("minishell: syntax error near unexpected token `");
			g_data->exit_status = 258;
			return (printf("%s'\n", tmp->words[0]), 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	count_commands(void)
{
	t_ms	*tmp;
	int		len;

	tmp = g_data->ms_list;
	len = 0;
	while (tmp)
	{
		if (tmp->type == 1)
			len++;
		tmp = tmp->next;
	}
	g_data->command = len + 1;
}

void	interpret_strings(void)
{
	if (check_syntax())
	{
		ret_signal(1);
		return ;
	}
	count_commands();
}
