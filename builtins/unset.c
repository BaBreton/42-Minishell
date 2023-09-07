/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:05:07 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 09:47:51 by babreton         ###   ########.fr       */
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

int	to_unset(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	fd;

	i = 0;
	if (ac != 2)
		return (printf("unset: not enough arguments\n"), 0);
	if (!to_unset(av[1]))
		return (0);
	fd = openfd(ev);
	while (ev[i])
	{
		if (!ft_strncmp(av[1], ev[i], ft_strlen(av[1])))
			i++;
		write(fd, ev[i], ft_strlen(ev[i]));
		i++;
	}
	close(fd);
	return (0);
}
