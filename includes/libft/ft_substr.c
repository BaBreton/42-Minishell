/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:46:16 by babreton          #+#    #+#             */
/*   Updated: 2023/02/17 07:32:11 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*array;
	int					i;

	i = 0;
	array = NULL;
	if (!s)
		return (NULL);
	if (start >= (ft_strlen(s)))
	{
		array = (char *)malloc(sizeof(char));
		if (!array)
			return (NULL);
		array[0] = '\0';
		return (array);
	}
	if (len > (ft_strlen(s)) - start)
		len = (ft_strlen(s)) - start;
	array = (char *)malloc((len + 1) * sizeof(char));
	if (!array)
		return (NULL);
	while (s[start] && len-- != 0)
		array[i++] = s[start++];
	array[i] = '\0';
	return (array);
}
