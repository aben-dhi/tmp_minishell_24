/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:40 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:52:02 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BRED "\e[1;31m"
# define RED "\033[0;31m"
# define YELLOW "\033[1;33m"
# define CX "\033[0m"
# define BLACK "\e[0;30m"
# define GREEN "\e[0;32m"
# define BGREEN "\e[1;32m"
# define BLUE "\e[0;34m"
# define PURPLE "\e[0;35m"
# define CYAN "\e[1;36m"
# define WHITE "\e[0;37m"
# define GREY "\e[1;30m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include "../includes/libft.h"

# define ERR "minishell: syntax error near unexpected token `|'\n"

extern int	g_signal;

typedef enum e_redir_spec
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ERROR,
	NONE,
}	t_redir_spec;

typedef struct s_redir
{
	char			*file;
	t_redir_spec	type;
}	t_redir;

typedef struct s_token
{
	char			*value;
	char			**args;
	t_redir			redir_in;
	t_redir			redir_out;
	char			*sep;
	struct s_token	*next;
}	t_token;

//**************parsing:******************//
t_token			*ft_parse(int *exit_stat, char *line, t_list *env);
char			*ft_expand(int *exit_stat, char *str, t_list *env);
t_token			*add_back(t_token **token, t_token *new);
t_token			*new_token(char *token);
t_token			*free_token(t_token *token);
t_token			*split_to_tokens(char *line, int *exit_stat);
void			init_tokens(t_token *token);
int				lexing(t_token *token, t_list *env);
int				get_file(char *line, t_token *token, \
t_redir_spec type, t_list *env);
char			*skip_quotes(char *token);
t_redir_spec	redirect_spec(char	*line);
t_redir_spec	check_outfile(char *str, int i);
t_redir_spec	check_infile(char *str, int i);
char			*get_heredoc(char *heredoc, t_list *env);

//*************execution:*****************//
void			ft_handler(int signal);
int				piping(t_token *token, t_list *env);
t_list			*ft_env_fill(char **env);

void			dup_std_fd(int *stdin_dup, int *stdout_dup);
void			restore_std_fd(int stdin_dup, int stdout_dup);
char			*ft_cmd(char **token, t_list *env);
int				ft_execute(t_token *token, t_list *env);
int				ft_redirect(char *file, t_redir_spec type);

//**************builtins:*****************//
int				builtin_check(char *cmd);
int				execute_builtin(t_token *token, t_list **env);
int				execute_env(t_list *env);
int				execute_pwd(void);
int				execute_cd(char **arg, t_list *env);
int				execute_echo(char **args);
int				execute_export(char **args, t_list *env);
int				execute_unset(char **arg, t_list **env);
int				execute_exit(char **arg);
int				ft_redir(char *file, t_redir_spec type);
int				modify_env(char *envar, char *enval, t_list *env);

//***************utils:*******************//
char			*join_n_free(char *s1, char *s2);
char			*join_char(char *s1, char c);
char			*get_envar(char *str, int i, int j);
char			*extract_enval(char *envar, t_list *env);
char			*ft_getenv(char *var, t_list *env);
void			skip_space(char *line, int *i);
char			*ft_next(char *token);
int				ft_count2(char *line);
int				skip_spaces(char *line, int i);
void			display_err(char *file, char *err);
int				open_redir_fd(char *file, t_redir_spec type);
void			free_arr(char **arr);
void			free_token_all(t_token *token);

#endif