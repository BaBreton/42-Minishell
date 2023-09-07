/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_chardup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:49:45 by babreton          #+#    #+#             */
/*   Updated: 2023/07/01 14:05:02 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**double_chardup(char **str, int size)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (size + 1));
	while (i <= size)
	{
		new[i] = ft_strdup(str[i]);
		i++;
	}
	return (new);
}
