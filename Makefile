FLAG= -Wall -Wextra -Werror #-fsanitize=address
NAME=minishell

SRC_DIR = src/
OBJ_DIR = obj/
LEX_DIR = Lexer/
EXP_DIR = Expansion/
PAR_DIR = Parser/

LEX_SRC = make_lexims.c tokenizer.c remove_node.c 
EXP_SRC = expansion.c expansion_utils.c wildcard.c
PAR_SRC = parser.c convert_args.c

SRC= main.c command_linked_list_stuff.c mini_parse.c built_in.c ft_unset.c  echo.c syntax_err.c\
	execution.c here_doc.c creat_env_list.c check_syntax.c export.c new_env.c cd.c check_syntax.c check_built.c\
	heredoc_utils.c redirection.c built_in2.c command_linked_list_stuff1.c execution_utils.c syntax_err_utils.c

OSRC = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OSRC += $(addprefix $(OBJ_DIR), $(LEX_SRC:.c=.o))
OSRC += $(addprefix $(OBJ_DIR), $(EXP_SRC:.c=.o))
OSRC += $(addprefix $(OBJ_DIR), $(PAR_SRC:.c=.o))

INCLUDES= -I includes

READ_LINE = -lreadline -L ${HOME}/homebrew/opt/readline/lib -I ${HOME}/homebrew/opt/readline/include


all : $(NAME)

$(NAME) : $(OSRC) src/signale_handel.c
	@make -C libft > /dev/null
	@$(CC) $(FLAG) $(READ_LINE) $(INCLUDES)  $^ libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/minishell.h 
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror  -c $< -o $@

$(OBJ_DIR)%.o: $(LEX_DIR)%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -c $< -o $@

$(OBJ_DIR)%.o: $(EXP_DIR)%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -c $< -o $@

$(OBJ_DIR)%.o: $(PAR_DIR)%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -c $< -o $@

clean :
	@make -C libft clean
	@rm -rf $(OBJ_DIR)
fclean : clean
	@make -C libft fclean
	@rm -rf $(NAME)

bonus: all

re : fclean all

.PHONY : all clean fclean re bonus
