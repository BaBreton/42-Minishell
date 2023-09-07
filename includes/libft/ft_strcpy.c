/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:58:19 by babreton          #+#    #+#             */
/*   Updated: 2023/04/06 12:58:41 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char	*src)
{
	int		len;
	char	*str;
	int		i;

	i = -1;
	len = ft_strlen(src);
	str = (char *)malloc(len * sizeof(char) + 1);
	while (src[++i])
		str[i] = src[i];
	str[i] = '\0';
	return (str);
}
