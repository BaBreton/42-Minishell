/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_base_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:29:35 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 09:29:42 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_base_path(char **ev)
{
	int	i;
	int	found;
	int	len;

	i = -1;
	found = 0;
	while (ev[++i])
	{
		if (ft_strncmp(ev[i], "BASEDIR=", 8) == 0)
		{
			found = 1;
			break ;
		}
	}
	if (found == 0)
		return (NULL);
	len = ft_strlen(ev[i] + 8);
	return (ft_strwdup(ev[i] + 8, len - 1));
}
