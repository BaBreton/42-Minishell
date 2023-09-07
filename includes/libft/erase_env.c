/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:59:59 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 10:02:25 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	erase_env(char **ev)
{
	char	*path;
	char	**args;
	pid_t	pid;

	path = get_base_path(ev);
	path = ft_strjoin(path, "/.env2");
	args = malloc(sizeof(char *) * 3);
	args[0] = ft_strdup("rm");
	args[1] = ft_strdup(path);
	args[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve("/bin/rm", args, ev);
	else
		waitpid(pid, NULL, 0);
	free(path);
	free_char(args, 3);
}
