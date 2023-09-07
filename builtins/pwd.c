/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:59:59 by babreton          #+#    #+#             */
/*   Updated: 2023/07/18 15:30:55 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft/libft.h"

int	main(int ac, char **av)
{
	char	pwd[1024];

	(void)ac;
	(void)av;
	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}
