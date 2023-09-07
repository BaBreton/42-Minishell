/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:09:37 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 15:56:54 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*g_data;

void	new_line(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!g_data->exit_status)
		ft_putstr_fd("\033[1;32m\033[1", 2);
	else
		ft_putstr_fd("\033[1;31m\033[1", 2);
	ft_putchar_fd(g_data->ev_user[0], 2);
	ft_putstr_fd(g_data->ev_user, 2);
	ft_putstr_fd("\033[0;37m", 2);
	ft_putstr_fd(" in ", 2);
	ft_putstr_fd("\e[1;93m", 2);
	ft_putstr_fd(pwd, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("\n", 2);
	free(pwd);
}

void	free_minishell(void)
{
	ms_clear(&g_data->ms_list);
	free(g_data->line);
	free(g_data->ev_dir);
	free(g_data->ms_dir);
	free(g_data->ev_user);
	close(g_data->old_fd[0]);
	close(g_data->old_fd[1]);
	rm_file(get_base_path(g_data->ev), "/.env", g_data->ev);
	if (g_data->ev_status)
		free_char(g_data->ev_path, get_char_size(g_data->ev_path));
	free_char(g_data->ev, get_char_size(g_data->ev));
	free(g_data);
}

void	reset_fd(void)
{
	dup2(g_data->old_fd[0], 0);
	dup2(g_data->old_fd[1], 1);
}

int	main(int ac, char **av, char **ev)
{
	g_data = malloc(sizeof(t_data));
	initialize_minishell(ac, av, ev);
	while (g_data->status)
	{
		reset_fd();
		new_line();
		g_data->input = readline("$> ");
		if (g_data->input == NULL)
			ctrl_d();
		check_new_line();
		if (g_data->nl_error == 0 || g_data->nl_error == 2)
		{
			add_history(g_data->input);
			if (g_data->nl_error == 0)
			{
				parsing_input();
				interpret_strings();
				if (g_data->exit_status != 258)
					execute_commands();
			}
		}
		free(g_data->input);
	}
	free_minishell();
	return (0);
}
