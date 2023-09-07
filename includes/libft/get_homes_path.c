/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_homes_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:07:55 by cparras           #+#    #+#             */
/*   Updated: 2023/07/25 10:37:57 by cparras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_homes_path(char **ev)
{
	char	*base_path;
	int		i;
	int		j;
	char	*line;

	i = -1;
	base_path = get_base_path(ev);
	while (base_path[++i])
	{
		if (base_path[i] == '/' && base_path[i + 1] == 'h'
			&& base_path[i + 2] == 'o')
		{
			i++;
			while (base_path[i] != '/')
				i++;
			break ;
		}
	}
	line = (char *)malloc(i * sizeof(char) + 2);
	j = -1;
	while (++j < i)
		line[j] = base_path[j];
	line[j] = '/';
	line[j + 1] = '\0';
	return (line);
}
