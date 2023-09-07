/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:51:41 by babreton          #+#    #+#             */
/*   Updated: 2023/07/18 15:30:49 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"

int	main(int ac, char **av, char **ev)
{
	int	i;

	(void)ac;
	(void)av;
	i = 1;
	if (!ev)
		printf("\n");
	while (ev[++i])
		printf("%s", ev[i]);
	return (0);
}
