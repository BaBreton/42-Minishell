/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printerr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:54:21 by babreton          #+#    #+#             */
/*   Updated: 2023/04/13 16:30:17 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printerr(char *error, int option)
{
	if (!error)
		return (-1);
	ft_printf("%s", error);
	if (option == 0)
		return (0);
	exit(0);
}
