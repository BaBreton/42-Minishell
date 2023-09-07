/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:07:36 by babreton          #+#    #+#             */
/*   Updated: 2023/05/16 11:24:31 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_str(char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = ft_calloc(sizeof(char), (len + 1));
	if (!new_str)
		return (NULL);
	return (new_str);
}
