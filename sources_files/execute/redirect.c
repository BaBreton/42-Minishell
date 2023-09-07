/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:54:28 by babreton          #+#    #+#             */
/*   Updated: 2023/07/18 17:02:31 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_redirections(t_ms *tmp)
{
	int	type;

	type = tmp->type;
	tmp = tmp->next;
	if (type == 2)
		g_data->redir_in = ft_strdup(tmp->words[0]);
	if (type == 3)
		g_data->redir_out = ft_strdup(tmp->words[0]);
	if (type == 4)
		g_data->redir_out = ft_strdup(tmp->words[0]);
	if (type == 5)
		g_data->redir_in = ft_strdup(tmp->words[0]);
}

int	here_doc(char *delimiter)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	printf("Enter here-doc content terminated by '%s':\n", delimiter);
	line = readline("heredoc> ");
	while (line)
	{
		line = dollar_check(line);
		if (ft_strncmp(line, delimiter, ft_strlen(line) - 1) == 0)
			break ;
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	redirect_in(void)
{
	int	fd;

	if ((g_data->redirect & (1 << 0)) != 0)
	{
		fd = open(g_data->redir_in, O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	if ((g_data->redirect & (1 << 3)) != 0)
	{
		fd = here_doc(g_data->redir_in);
		dup2(fd, 0);
		close(fd);
	}
}

void	redirect_out(void)
{
	int	fd;

	if ((g_data->redirect & (1 << 1)) != 0)
	{
		fd = open(g_data->redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
		close(fd);
	}
	if ((g_data->redirect & (1 << 2)) != 0)
	{
		fd = open(g_data->redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, 1);
		close(fd);
	}
}

void	redirect(int option)
{
	if (!option)
		redirect_in();
	else
		redirect_out();
}
