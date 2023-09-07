/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:39:39 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 11:05:37 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"

int	openfd(char **ev)
{
	int		i;
	int		found;
	int		fd;
	char	*path;

	i = -1;
	found = 0;
	while (ev[++i])
	{
		if (!ft_strncmp("BASEDIR=", ev[i], 8))
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (-1);
	found = ft_strlen(ev[i] + 8);
	path = ft_strwdup(ev[i] + 8, found - 1);
	path = ft_strjoin(path, "/.env");
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(path);
	return (fd);
}

char	*get_shlvl(char **ev)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	path = get_base_path(ev);
	path = ft_strjoin(path, "/.env");
	while (ev[++i])
		if (!ft_strncmp("SHLVL=", ev[i], 6))
			break ;
	i = ft_atoi(ev[i] + 6) + 1;
	free(path);
	tmp = ft_itoa(i);
	path = ft_strbjoin("SHLVL=", tmp);
	path = ft_strjoin(path, "\n");
	free(tmp);
	return (path);
}

int	main(int ac, char **av, char **ev)
{
	char	*path;
	int		i;
	int		fd;

	(void)ac;
	(void)av;
	path = get_shlvl(ev);
	i = -1;
	fd = openfd(ev);
	while (ev[++i])
	{
		if (!ft_strncmp("SHLVL=", ev[i], 6))
			write(fd, path, ft_strlen(path));
		else
			write(fd, ev[i], ft_strlen(ev[i]));
	}
	free(path);
	close(fd);
	return (0);
}
