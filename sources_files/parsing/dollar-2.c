/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar-2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:40:56 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 17:13:24 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_new_line(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '\n')
			j++;
	tmp = malloc(sizeof(char) * (j + 1));
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '\n')
			tmp[j++] = str[i];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*check_inter(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '?')
	{
		free(str);
		str = malloc(sizeof(char) * 2);
		str[0] = 'R';
		str[1] = '\0';
	}
	return (str);
}

char	*get_env(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_data->ev[++i])
	{
		if (ft_strncmp(g_data->ev[i], str, ft_strlen(str)) == 0)
		{
			tmp = ft_strdup(g_data->ev[i] + ft_strlen(str) + 1);
			free(str);
			tmp = remove_new_line(tmp);
			return (tmp);
		}
	}
	free(str);
	return (ft_strdup(""));
}

char	*get_rest(char *str, int i)
{
	char	*new_str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	i -= 1;
	while (str[i++])
		j++;
	new_str = malloc(sizeof(char) * (j + 1));
	i -= j + 1;
	while (str[++i])
		new_str[k++] = str[i];
	new_str[k] = '\0';
	return (new_str);
}

char	*get_first_part(char *str)
{
	char	*new_str;
	int		i;

	i = -1;
	while (str[++i] != '$')
		;
	new_str = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != '$')
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}
