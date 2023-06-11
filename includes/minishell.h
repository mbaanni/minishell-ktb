#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/signal.h>
#include <sys/termios.h>
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>

/*typedef struct t_redir{
	int		type;
	char	*file_name;
	int 	is_expand;
	struct t_redir *next;
} t_redir;*/

/*enum  e_cmd_redir_types{
	IN,
	OUT,
	//APPEND,
	//HERE_DOC
};*/


/*typedef struct t_command{
	char				*command_path;
	char				**command_args;
	int					is_valid;
	t_redir		*command_redirections;
	struct t_command	*next;
} t_command;*/



typedef enum toke_state
{
	INDQUOTE,
	INSQUOTE,
	GENERAL,
} state;

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
} t_token;

typedef struct s_lexim
{
	char	*content;
	t_token	token;
	state	lexim_state;
	int is_redir;
	struct s_lexim *prev;
	struct s_lexim *next;
} t_lexim;

typedef struct s_redir
{
	t_token 	token;
	char		*file;
	int			is_expand;
	struct s_redir *next; 
}	t_redir;

typedef struct s_env
{
	char	*id;
	char	*data;
	int		i;
	struct s_env *next;
}t_env;

typedef struct s_command{
	char				*command_path;
	char				**command_args;
	int					is_valid;
	t_redir				*command_redirections;
	struct s_command	*next;
} t_command;


typedef struct s_cmd
{
	t_lexim	 	*args;
	t_redir		*redirs;
	struct s_cmd *next;
}	t_cmd;


/******EXPANSION UTILS******/
char	*find_in_env(char *str, int len);
int		lent_identifier(char *str);
char	*expand_var(char *str);
t_lexim	*new_lexim(char *str);
int		should_parse(char	*str);
/***************************/

char		**get_args(t_list *cmd);
void		cmdadd_back(t_command **cmds, t_command *newcmd);
t_command	*new_cmd(char	**args);
t_command	*convert_args(t_cmd *cmds);

t_cmd	*ft_expand(t_cmd *cmds, int nb_cmds);
void	add_back(t_lexim **head, t_lexim *new_lexim);
void	tokenize_elements(t_lexim *lexims);
void	parse_env(t_lexim *lexims);
char	*parse_string(char	*str);
t_cmd	*parse_commands(t_lexim *lexims);

//####### General structer #######//
typedef struct s_general{

	t_command	*command_head;
	t_env 		*env_head;
	int			exit_status;
	int			command_count;
	char		**ev;
	int			sig;
	int			prev[2];
	int			next[2];
}	t_general;

extern t_general *general;


t_command		*ft_new_command(char	*command_path, char **command_args, t_redir *command_redirections, int is_valid);
t_redir			*generate_cmd_redirs(int type, char *file_name);
t_redir			*ft_last_redir(t_redir *lst);
t_env			*creat_env(char **ev);
int 			check_token_syntax(t_lexim *lexim);
void			ft_command_add_back(t_command **head, t_command *cmd);
int				ft_commands_size(t_command *lst);
void			ft_redir_add_back(t_redir **head, t_redir *cmd);
void			find_path();
char			*ft_strchr_data(char *str);
void			ft_env_add_back(t_env **head, t_env *evirement);
int				here_doc(t_redir *redir);
void			executing_phase();
char		    **set_new_env();
int			    redirection_handler(t_command *commands, int fdin, int fdout);
int				index_signe(char *str);
void			ft_env_add_back(t_env **head, t_env *evirement);
t_env			*ft_last_env(t_env *lst);
int				check_syntax(char *str);
void			signal_to_take();
int				check_for_built_in(t_command *cmd, int i);
char			*ft_getenv(char *str);
int				is_expand(char *str);
t_lexim			*convert_to_lexims(char	*str);


//####################################################################
//#							built_in								 #
//####################################################################
void	ft_echo(t_command *cmds);
void	ft_cd(t_command *cmds);
void	ft_exit(t_command *cmd);
void	ft_export(t_command *cmd);
void    ft_unset(t_command *cmd);
void	ft_pwd();
void	ft_env();
#endif
