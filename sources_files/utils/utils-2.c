/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:49:57 by babreton          #+#    #+#             */
/*   Updated: 2023/07/18 11:44:35 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_first_char(void)
{
	char	*tmp;
	char	*tmp2;

	tmp = g_data->input;
	tmp2 = ft_strbjoin(" ", tmp);
	free(tmp);
	return (tmp2);
}

void	print_ms_list(void)
{
	t_ms	*tmp;
	int		i;

	tmp = g_data->ms_list;
	i = -1;
	while (tmp)
	{
		i = -1;
		printf("--------------------\033[0m\n");
		while (tmp->words[++i])
			printf("\t%s\n", tmp->words[i]);
		printf("--                --\n");
		printf("  \033[0;90mtype: \033[1m%d\033[0m\n", tmp->type);
		printf("  \033[0;33msize: \033[1m%d\033[0m\n", tmp->size);
		printf("--------------------\033[0m\n");
		if (tmp->next != NULL)
			printf("\033[0;47mMaillon suivant ->  \033[0m\n");
		else
			printf("Dernier maillon\n");
		tmp = tmp->next;
	}
}

t_ms	*get_cmd_location(int i)
{
	t_ms	*tmp;
	int		j;

	tmp = g_data->ms_list;
	j = 0;
	while (tmp)
	{
		if (j == i)
			return (tmp);
		if (tmp->type == 1)
			j++;
		tmp = tmp->next;
	}
	return (NULL);
}

void	ret_loop(char *str)
{
	int	i;

	i = -1;
	while (g_data->ev[++i])
	{
		if (ft_strncmp(g_data->ev[i], "R=", 2) == 0)
		{
			free(g_data->ev[i]);
			g_data->ev[i] = ft_strdup(str);
			free(str);
			return ;
		}
	}
	free(str);
}

void	ret_signal(int option)
{
	char	*str;
	char	*nb;

	if (!option)
	{
		if (WIFEXITED(g_data->ret))
			g_data->exit_status = WEXITSTATUS(g_data->ret);
		if (WIFSIGNALED(g_data->ret))
			g_data->exit_status = WTERMSIG(g_data->ret);
		if (WCOREDUMP(g_data->ret))
			g_data->exit_status = WCOREDUMP(g_data->ret);
		if (g_data->ret == 256)
			g_data->exit_status = 1;
	}
	str = malloc(sizeof(char) * 3);
	str[0] = 'R';
	str[1] = '=';
	str[2] = '\0';
	nb = ft_itoa(g_data->exit_status);
	str = ft_strjoin(str, nb);
	str = ft_strjoin(str, "\n");
	ret_loop(str);
	free(nb);
	update_env_fd();
}
