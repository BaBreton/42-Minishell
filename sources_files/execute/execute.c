/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:45:52 by babreton          #+#    #+#             */
/*   Updated: 2023/07/24 15:44:24 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_free(char *path, char **words)
{
	if (g_data->redir_in)
		free(g_data->redir_in);
	if (g_data->redir_out)
		free(g_data->redir_out);
	if (path)
		free(path);
	free_char(words, get_char_size(words));
}

void	update(void)
{
	int		fd;
	char	*line;

	if (g_data->updater == 2)
	{
		line = ft_strbjoin(g_data->ms_dir, "/.dir");
		fd = open(line, O_RDONLY);
		free(line);
		line = get_next_line(fd);
		if (chdir(line) == -1)
		{
			g_data->exit_status = 1;
			ret_signal(0);
		}
		free(line);
		close(fd);
	}
	free_char(g_data->ev, get_char_size(g_data->ev));
	g_data->ev = NULL;
	g_data->exit_status = 0;
	update_env();
	if (g_data->updater == 2 && g_data->ret == 0)
		rm_file(get_base_path(g_data->ev), "/.dir", g_data->ev);
}

int	last_command(char *path, char **words)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (g_data->cmd_error = 1, printf("minishell: fork error\n"));
	if (pid == 0)
	{
		redirect(0);
		redirect(1);
		if (execve(path, words, g_data->ev) == -1)
			return (g_data->cmd_error = 1, printf("minishell: execve error\n"));
	}
	else
	{
		dup2(g_data->old_fd[1], 1);
		waitpid(pid, &g_data->ret, 0);
	}
	return (0);
}

int	current_commands(char *path, char **words)
{
	pid_t	pid;

	if (pipe(g_data->fd) == -1)
		return (g_data->cmd_error = 1, printf("minishell: pipe error\n"));
	pid = fork();
	if (pid == -1)
		return (g_data->cmd_error = 1, printf("minishell: fork error\n"));
	if (pid == 0)
	{
		redirect(0);
		redirect(1);
		close(g_data->fd[0]);
		if (!g_data->redir_out)
			dup2(g_data->fd[1], 1);
		if (execve(path, words, g_data->ev) == -1)
			return (g_data->cmd_error = 1, printf("minishell: execve error\n"));
	}
	else
	{
		waitpid(pid, &g_data->ret, 0);
		close(g_data->fd[1]);
		dup2(g_data->fd[0], 0);
	}
	return (0);
}

void	execute_commands(void)
{
	int		i;
	char	**words;
	char	*path;

	i = 0;
	while (i < g_data->command)
	{
		new_command_init();
		check_redirections(i);
		words = get_command_words(i);
		path = get_path(words[0]);
		if (!path)
			return (path_error(words[0], words));
		if (i < g_data->command - 1)
			current_commands(path, words);
		else
			last_command(path, words);
		if (g_data->cmd_error)
			return ;
		if (g_data->updater)
			update();
		ret_signal(0);
		i++;
		command_free(path, words);
	}
}
