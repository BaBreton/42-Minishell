/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:49:11 by babreton          #+#    #+#             */
/*   Updated: 2023/02/17 07:40:53 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	if ((!len || !big) && !len)
		return (NULL);
	while (*big && len >= ft_strlen(little))
	{
		i = 0;
		while (big[i] == little[i] && i < len)
		{
			if (!little[i + 1])
				return ((char *)big);
			i++;
		}
		big++;
		len--;
	}
	return (NULL);
}
