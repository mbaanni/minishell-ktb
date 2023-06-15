/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 20:27:54 by mbaanni           #+#    #+#             */
/*   Updated: 2023/06/15 13:00:57 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/get_next_line.h"
# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/signal.h>
# include <sys/termios.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum toke_state
{
	INDQUOTE,
	INSQUOTE,
	GENERAL,
}						t_state;

typedef enum s_token
{
	WORD = '0',
	ENV = '$',
	PIPE = '|',
	RDIRIN = '<',
	RDIROUT = '>',
	HERE_DOC = 'h',
	APPEND = 'A',
	SPACES = ' ',
	TABS = '\t',
}						t_token;

typedef struct s_lexim
{
	char				*content;
	t_token				token;
	t_state				lexim_t_state;
	int					is_redir;
	struct s_lexim		*prev;
	struct s_lexim		*next;
}						t_lexim;

typedef struct s_redir
{
	t_token				token;
	char				*file;
	int					is_expand;
	struct s_redir		*next;
}						t_redir;

typedef struct s_env
{
	char				*id;
	char				*data;
	int					i;
	struct s_env		*next;
}						t_env;

typedef struct s_command
{
	char				*command_path;
	char				**command_args;
	int					is_valid;
	t_redir				*command_redirections;
	struct s_command	*next;
}						t_command;

typedef struct s_cmd
{
	t_lexim				*args;
	t_redir				*redirs;
	struct s_cmd		*next;
}						t_cmd;

/******WILD CARD************/
t_lexim					*find_matching(char *pattern);
/***************************/

/******EXPANSION UTILS******/
char					*find_in_env(char *str, int len);
int						lent_identifier(char *str);
char					*expand_var(char *str);
t_lexim					*new_lexim(char *str);
void					replace_str(char *str);
/***************************/

char					**get_args(t_list *cmd);
void					cmdadd_back(t_command **cmds, t_command *newcmd);
t_command				*new_cmd(char **args);
t_command				*convert_args(t_cmd *cmds);
void					add_back(t_lexim **head, t_lexim *new_lexim);
t_lexim					*new_lexim(char *str);
int						count_chars_for_quotes(char *str);
int						count_chars_for_env(char *str);
int						count_chars_for_rep(char *str);
t_cmd					*ft_expand(t_cmd *cmds, int nb_cmds);
void					add_back(t_lexim **head, t_lexim *new_lexim);
void					tokenize_elements(t_lexim *lexims);
void					parse_env(t_lexim *lexims);
char					*parse_string(char *str);
t_cmd					*parse_commands(t_lexim *lexims, t_cmd *cmds, int	i);
int						should_parse(char *str);
t_lexim					*new_lex(char *str, t_token type);
t_redir					*new_redir(t_token token, char *file);
void					redir_add_back(t_redir **head, t_redir *redir);
int						n_cmds(t_lexim *lexims);
t_redir					*last_node(t_redir *redirs);
char	*get_arg(char *str);
int	parsing_processing(char *str, char c, int i, char **s2);

//####### General structer #######//
typedef struct s_general
{
	t_command			*command_head;
	t_env				*env_head;
	int					exit_status;
	int					command_count;
	char				**ev;
	int					_hx;
	int					sig;
	unsigned int		old_c_lflag;
	struct termios		_terminal;
	int					prev[2];
	int					next[2];
}						t_general;

extern t_general		*g_grl;
//##########################################################
//							ENV_FUNC						#
//##########################################################
t_env					*creat_env(char **ev);
void					ft_env_add_back(t_env **head, t_env *evirement);
char					**set_new_env(void);
char					*ft_getenv(char *str);

//###########################################################
//						heredoc								#
//###########################################################
int						lent_identifiers(char *str);
char					*find_in_envs(char *str, int len);
int						ft_lstrcmp(char *s1, char *s2);
int						set_file(char *str);
//###########################################################################
t_command				*ft_new_command(char *command_path, char **command_args,
							t_redir *command_redirections, int is_valid);
t_redir					*generate_cmd_redirs(int type, char *file_name);
t_redir					*ft_last_redir(t_redir *lst);
int						check_token_syntax(t_lexim *lexim);
void					ft_command_add_back(t_command **head, t_command *cmd);
int						ft_commands_size(t_command *lst);
void					ft_redir_add_back(t_redir **head, t_redir *cmd);
void					find_path(void);
char					*ft_strchr_data(char *str);
int						here_doc(t_redir *redir);
void					executing_phase(void);
void					add_new_env(int i, char **args);
int						redirection_handler(t_command *commands, int fdin,
							int fdout);
int						index_signe(char *str);
char					*ft_trime_side(char *str);
t_env					*ft_last_env(t_env *lst);
int						check_syntax(char *str);
void					handle_signal(int sig);
int						check_for_built_in(t_command *cmd, int i);
int						is_expand(char *str);
t_lexim	*convert_to_lexims(char *str, int i, t_lexim *lexims);
int						ft_strcmps(char *s1, char *s2);
void					check_file_exist(char *str);
int						one_cmd(t_command *commands);
void					child_work1(t_command *commands);
void					child_work(int fd, int i, t_command *commands,
							char **new_env);
int						unseted_path(char *str);
char	*sub_keycode(char *str);
void	replace_str(char *str);
int	check_ambigious(char *str);
int	is_space(char *str);
int	is_wild(char *str);
void	add_args(t_lexim *tmp_lexim, char **args);
void	assign_values(char **args, t_lexim **tmp_lexim);
t_lexim	*get_value(t_lexim *tmp_lexim, t_lexim **tmp_next);
t_lexim	*expand_env(t_lexim *tmp_lexim);
t_lexim	*expand_wild_card_utils(t_lexim *tmp_lexim, t_lexim *tmp_next,
		char *astrik);
//####################################################################
//#							built_in									#
//####################################################################
void					ft_echo(t_command *cmds);
void					ft_cd(t_command *cmds);
void					ft_exit(t_command *cmd);
void					ft_export(t_command *cmd);
void					ft_unset(t_command *cmd);
void					ft_pwd(void);
void					ft_env(void);
#endif
