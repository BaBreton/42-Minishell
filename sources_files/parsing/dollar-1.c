/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar-1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:38:08 by babreton          #+#    #+#             */
/*   Updated: 2023/07/14 17:46:06 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_dollar_str(char *str)
{
	char	*new_str;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	while (str[++i] && _char(str[i], str[i - 1]))
		j++;
	new_str = malloc(sizeof(char) * (j + 2));
	i = 0;
	j = 0;
	while (str[i] != '$')
		i++;
	while (_char(str[i], '\0'))
		new_str[j++] = str[++i];
	new_str[j] = '\0';
	if (new_str[j - 1] == ' ' || new_str[j - 1] == '\'')
		new_str[j - 1] = '\0';
	new_str = check_inter(new_str);
	tmp = get_env(new_str);
	return (tmp);
}

char	*quote_dollar(char *str, char *tmp)
{
	char	*str1;
	char	*str2;
	char	*new_str;
	int		i;

	str1 = get_first_part(str);
	str1 = ft_strjoin(str1, tmp);
	i = -1;
	while (str[++i] != '$')
		;
	while (str[++i] && _char(str[i], str[i - 1]))
		;
	str2 = get_rest(str, i);
	new_str = ft_strjoin(str1, str2);
	free(str2);
	return (new_str);
}

char	*replace_dollar(char *str)
{
	char	*new_str;
	char	*tmp;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			return (str);
	tmp = get_dollar_str(str);
	new_str = quote_dollar(str, tmp);
	free(tmp);
	free(str);
	return (new_str);
}

char	*dollar_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			break ;
		if (str[i] == '$')
			str = replace_dollar(str);
	}
	return (str);
}
