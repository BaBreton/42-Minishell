/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:36:52 by cparras           #+#    #+#             */
/*   Updated: 2023/07/20 09:45:36 by babreton         ###   ########.fr       */
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

int	check_format(char **str, int ac)
{
	int	i;

	i = 0;
	(void)ac;
	while (str[1][i] && str[1][i] != '=')
		i++;
	if (str[1][i] == '\0')
		return (0);
	if (!str[2])
	{
		if (str[1][i + 1] == '=' || str[1][i + 1] == '\0')
			return (0);
		else
			return (i);
	}
	else
		return (i);
	return (0);
}

char	*create_string(char **strs, int i)
{
	char	*string;

	string = NULL;
	if (i == 2)
	{
		string = ft_strdup(strs[1]);
		return (ft_strjoin(string, "\n"));
	}
	string = ft_strdup(strs[1]);
	string = ft_strjoin(string, strs[2]);
	string = ft_strjoin(string, "\n");
	return (string);
}

int	main(int ac, char **av, char **ev)
{
	int		i;
	int		fd;
	char	*txp;
	int		len;
	int		w;

	i = -1;
	w = 0;
	len = check_format(av, ac);
	if (len == 0)
		return (0);
	txp = create_string(av, ac);
	fd = openfd(ev);
	while (ev[++i])
	{
		if (!ft_strncmp(txp, ev[i], len + 1))
			write(fd, txp, ft_strlen(txp + w++));
		else
			write(fd, ev[i], ft_strlen(ev[i]));
	}
	if (w == 0)
		write(fd, txp, ft_strlen(txp));
	close(fd);
	free(txp);
	return (0);
}
