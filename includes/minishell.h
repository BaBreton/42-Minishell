/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babreton <babreton@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 23:05:53 by babreton          #+#    #+#             */
/*   Updated: 2023/07/20 11:14:48 by babreton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>

typedef struct s_qlist
{
	char				*str;
	int					type;
	struct s_qlist		*next;
}						t_qlist;

typedef struct s_ms
{
	char			**words;
	int				type;
	int				size;
	struct s_ms		*next;
}					t_ms;

typedef struct s_data
{
	char		**ev;
	char		**ev_path;
	char		*ev_user;
	int			ev_status;
	char		*line;
	int			status;
	int			exit_status;
	int			old_fd[2];
	char		*input;
	int			nl_error;
	int			first_call;
	int			command;
	int			redirect;
	int			nb_redirect;
	int			builtin;
	int			fd[2];
	int			cmd_error;
	char		*redir_in;
	char		*redir_out;
	int			ret;
	int			updater;
	char		*ev_dir;
	char		*ms_dir;
	t_qlist		*q_list;
	t_ms		*ms_list;
}		t_data;

extern t_data	*g_data;

/*---ms-type---*/
/*
	0 - command
	1 - pipe
	2 - <
	3 - >
	4 - >>
	5 - <<
	6 - ;
	7 - &
*/

/*-----Q-LIST-----*/
t_qlist	*qlist_new(char *str, int type);
t_qlist	*qlist_last(t_qlist *lst);
void	qlist_add_back(t_qlist **lst, t_qlist *new);
void	qlist_clear(t_qlist **lst);

/*-----MS-LIST-----*/
t_ms	*ms_new(char **content, int type, int size);
t_ms	*ms_last(t_ms *lst);
void	ms_back(t_ms **lst, t_ms *new);
void	ms_clear(t_ms **lst);

/*-----UTILS-----*/
void	sigquit_handler(int sig);
void	show_ctl(int sig);
int		handle_signal(void);
void	sig_handler_sa(int signal, siginfo_t *info, void *context);
void	ctrl_d(void);
char	*add_first_char(void);
void	print_ms_list(void);
t_ms	*get_cmd_location(int i);
void	ret_signal(int option);
void	update_env_fd(void);
void	new_line(void);
void	rm_file(char *path, char *file, char **ev);
int		check_lvl(void);
void	level_down(void);

/*-----INITIALIZATION-----*/
void	free_minishell(void);
void	initialize_minishell(int ac, char **av, char **ev);
void	update_env(void);
char	*get_line(void);

/*-----PARSING-----*/
void	parsing_input(void);
	/*---NEW-LINE---*/
void	check_new_line(void);
	/*---FIRST-LIST---*/
void	first_list(void);
void	copy_quote_str(char *str, int *i, char type, int space);
int		count_quote_str(int j, char type);
char	*join_str(char *first_str, int *i);
char	*dollar_check(char *str);
char	*get_rest(char *str, int i);
char	*check_inter(char *str);
char	*get_env(char *str);
char	*get_first_part(char *str);
	/*---SECOND-LIST---*/
void	second_list(void);

/*-----INTERPRET-----*/
void	interpret_strings(void);

/*-----EXECUTE-----*/
void	execute_commands(void);
void	command_free(char *path, char **words);
	/*---INIT---*/
void	new_command_init(void);
int		get_words_size(t_ms *tmp);
char	**add_after_redirections(t_ms *tmp, char **words);
char	**get_command_words(int i);
void	check_redirections(int i);
	/*---PATH---*/
char	*check_builtin(char *str);
char	*path_loop(char *str, char **path_list, int i, int found);
char	*get_path(char *str);
void	path_error(char *str, char **words);
	/*---REDIRECTION---*/
void	redirect(int option);
void	copy_redirections(t_ms *tmp);

#endif