/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:57:51 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 16:44:47 by cparras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	rm_file(char *path, char *file, char **ev)
{
	char	**args;
	pid_t	pid;

	path = ft_strjoin(path, file);
	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("rm");
	args[1] = ft_strdup(path);
	args[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", args, ev);
	else
		waitpid(pid, NULL, 0);
	free_char(args, 3);
	free(path);
}

int	check_lvl(void)
{
	int	i;
	int	lvl;

	i = -1;
	while (g_data->ev[++i])
		if (!ft_strncmp("SHLVL=", g_data->ev[i], 6))
			break ;
	lvl = ft_atoi(g_data->ev[i] + 6);
	return (lvl);
}

void	level_down(void)
{
	int		i;
	int		lvl;
	char	*tmp;

	i = -1;
	while (g_data->ev[++i])
		if (!ft_strncmp("SHLVL=", g_data->ev[i], 6))
			break ;
	lvl = ft_atoi(g_data->ev[i] + 6) - 1;
	tmp = ft_itoa(lvl);
	free(g_data->ev[i]);
	g_data->ev[i] = ft_strbjoin("SHLVL=", tmp);
	g_data->ev[i] = ft_strjoin(g_data->ev[i], "\n");
	free(tmp);
}
