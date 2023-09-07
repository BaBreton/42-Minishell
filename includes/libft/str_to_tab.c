/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:19:56 by babreton          #+#    #+#             */
/*   Updated: 2023/07/07 14:36:09 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//create me a function that takes a char ** and a char *
//and return a char ** with the char * added at the end

char	**copy_tab(char **tab, int size, int option)
{
	int		i;
	char	**new_tab;

	i = -1;
	new_tab = (char **)malloc(sizeof(char *) * (size + 1));
	while (++i < size)
	{
		if (option == 0 || option == 2)
			new_tab[i] = ft_strdup(tab[i]);
		else
			new_tab[i] = tab[i];
	}
	return (new_tab);
}

char	**str_to_tab(char **tab, char *str, int size, int option)
{
	int		i;
	char	**new_tab;

	i = -1;
	new_tab = copy_tab(tab, size, option);
	while (++i < size)
		;
	if (str != NULL)
	{
		if (option == 0)
			new_tab[i] = ft_strdup(str);
		else
			new_tab[i] = str;
	}
	else
		new_tab[size] = NULL;
	i = -1;
	if (option == 0 || option == 2)
	{
		while (++i < size)
			free(tab[i]);
		free(tab);
	}
	return (new_tab);
}
