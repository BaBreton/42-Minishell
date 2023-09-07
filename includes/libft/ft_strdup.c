/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 20:12:24 by babreton          #+#    #+#             */
/*   Updated: 2023/06/26 17:38:23 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*array;

	if (!s)
		return (NULL);
	size = ft_strlen(s) + 1;
	array = (char *)malloc(size * sizeof(char));
	if (!array)
		return (NULL);
	ft_memcpy(array, s, size);
	return (array);
}
