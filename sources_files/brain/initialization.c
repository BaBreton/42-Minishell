/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:20:36 by babreton          #+#    #+#             */
/*   Updated: 2023/07/25 10:14:53 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env_fd(void)
{
	int		fd;
	int		i;
	char	*path;

	path = ft_strbjoin(g_data->ms_dir, "/.env");
	fd = open(path, O_RDWR | O_TRUNC, 0644);
	free(path);
	i = -1;
	while (g_data->ev[++i])
		write(fd, g_data->ev[i], ft_strlen(g_data->ev[i]));
	close(fd);
}

void	update_env(void)
{
	int		fd;
	int		i;
	char	*tmp;

	fd = open(g_data->ev_dir, O_RDONLY, 0644);
	i = count_lines(fd);
	if (close(fd) == -1)
		perror("close");
	fd = open(g_data->ev_dir, O_RDONLY, 0644);
	g_data->ev = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = get_next_line(fd);
	while (tmp)
	{
		g_data->ev[i] = ft_strdup(tmp);
		free(tmp);
		tmp = get_next_line(fd);
		i++;
	}
	g_data->ev[i] = NULL;
	if (close(fd) == -1)
		perror("close");
}

void	initialize_env(char **ev)
{
	int	i;
	int	fd;

	i = -1;
	fd = open(".env", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (ev[++i])
	{
		write(fd, ev[i], ft_strlen(ev[i]));
		write(fd, "\n", 1);
	}
	if (g_data->ev_status == 0)
	{
		write(fd, "USER=", 5);
		write(fd, g_data->ev_user, ft_strlen(g_data->ev_user));
		write(fd, "\n", 1);
		write(fd, "SHLVL=1\n", 8);
		write(fd, "HOME=/nfs/home/", 15);
		write(fd, g_data->ev_user, ft_strlen(g_data->ev_user));
		write(fd, "\n", 1);
	}
	write(fd, "BASEDIR=", 8);
	write(fd, g_data->ms_dir, ft_strlen(g_data->ms_dir));
	write(fd, "\n", 1);
	write(fd, "R=0\n", 4);
	close(fd);
}

void	check_env_status(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
			g_data->ev_path = ft_split(ev[i] + 5, ':');
		if (ft_strncmp(ev[i], "USER=", 5) == 0)
			g_data->ev_user = ft_strdup(ev[i] + 5);
		i++;
	}
	if (i != 0)
		g_data->ev_status = 1;
	else
	{
		g_data->ev_status = 0;
		g_data->ev_path = NULL;
		g_data->ev_user = readline("Please enter an username: ");
	}
}

void	initialize_minishell(int ac, char **av, char **ev)
{
	(void)ac;
	(void)av;
	check_env_status(ev);
	g_data->ms_dir = getcwd(NULL, 0);
	g_data->ev_dir = ft_strjoin(getcwd(NULL, 0), "/.env");
	initialize_env(ev);
	update_env();
	g_data->line = ft_strbjoin(g_data->ev_user, "@minishell$> ");
	g_data->status = 1;
	g_data->exit_status = 0;
	g_data->old_fd[0] = dup(0);
	g_data->old_fd[1] = dup(1);
	g_data->first_call = 1;
	g_data->cmd_error = 0;
	show_ctl(0);
	signal(SIGQUIT, sigquit_handler);
	handle_signal();
}
