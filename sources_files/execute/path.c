/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:21:57 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 10:55:40 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (g_data->status = 0, 1);
	else if (ft_strncmp(str, "./minishell", 12) == 0)
		return (g_data->updater = 3, 1);
	return (0);
}

char	*check_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (ft_strbjoin(g_data->ms_dir, "/builtins/echo"));
	else if (ft_strncmp(str, "env", 4) == 0)
		return (ft_strbjoin(g_data->ms_dir, "/builtins/env"));
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (ft_strbjoin(g_data->ms_dir, "/builtins/pwd"));
	else if (ft_strncmp(str, "export", 6) == 0)
	{
		g_data->updater = 1;
		return (ft_strbjoin(g_data->ms_dir, "/builtins/export"));
	}
	else if (ft_strncmp(str, "cd", 3) == 0)
	{
		g_data->updater = 2;
		return (ft_strbjoin(g_data->ms_dir, "/builtins/cd"));
	}
	else if (ft_strncmp(str, "unset", 6) == 0)
	{
		g_data->updater = 1;
		return (ft_strbjoin(g_data->ms_dir, "/builtins/unset"));
	}
	else if (ft_strncmp(str, "./minishell", 12) == 0)
		return (ft_strbjoin(g_data->ms_dir, "/builtins/ms"));
	return (NULL);
}

char	*path_loop(char *str, char **path_list, int i, int found)
{
	char	*path;
	char	*tmp;

	while (path_list[++i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, str);
		if (open(path, O_RDONLY) != -1)
		{
			found = 1;
			break ;
		}
		free(path);
	}
	if (found == 1)
	{
		while (path_list[++i])
			free(path_list[i]);
		free(path_list);
		return (path);
	}
	free(path_list);
	return (NULL);
}

char	*get_path(char *str)
{
	char	*path;
	char	*tmp;
	char	**path_list;
	int		i;
	int		found;

	if (is_builtin(str))
		return (g_data->builtin = 1, check_builtin(str));
	if (g_data->ev_status == 0)
		return (NULL);
	tmp = ft_strtrim(ft_strdup(str), " ");
	if (access(tmp, F_OK) == 0)
		return (tmp);
	i = -1;
	found = 0;
	path = NULL;
	path_list = ft_split(getenv("PATH"), ':');
	path = path_loop(tmp, path_list, i, found);
	free(tmp);
	if (path)
		return (path);
	return (NULL);
}

void	path_error(char *str, char **words)
{
	if (g_data->status == 1)
	{
		printf("minishell: %s: command not found\n", str);
		g_data->exit_status = 127;
		free_char(words, get_char_size(words));
		ret_signal(1);
	}
	else
		command_free(NULL, words);
}
