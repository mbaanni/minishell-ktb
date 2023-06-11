FLAG= -Wall -Wextra -Werror #-fsanitize=address
NAME=minishell

SRC_DIR = src/
OBJ_DIR = obj/
LEX_DIR = Lexer/

LEX_SRC = make_lexims.c tokenizer.c parser.c expansion.c \
	   expansion_utils.c convert_args.c 
SRC= command_linked_list_stuff.c mini_parse.c built_in.c ft_unset.c signale_handel.c echo.c syntax_err.c\
	execution.c here_doc.c creat_env_list.c check_syntax.c export.c new_env.c cd.c check_syntax.c check_built.c

OSRC = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
OSRC += $(addprefix $(OBJ_DIR), $(LEX_SRC:.c=.o))

INCLUDES= -I includes

READ_LINE = -lreadline -L ${HOME}/homebrew/opt/readline/lib -I${HOME}/homebrew/opt/readline/include
#READ_LINE = -lreadline -L ${HOME}/brew/homebrew/opt/readline/lib -I${HOME}/brew/homebrew/opt/readline/include

all : $(NAME)

$(NAME) : $(OSRC)
	@make -C libft > /dev/null
	@$(CC) $(FLAG) $(READ_LINE) $(INCLUDES)  $^ src/main.c libft/libft.a -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -c $< -o $@

$(OBJ_DIR)%.o: $(LEX_DIR)%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@$(CC) -Wall -Wextra -Werror -c $< -o $@

clean :
	@make -C libft clean
	@rm -rf $(OBJ_DIR)
fclean : clean
	@make -C libft fclean
	@rm -rf $(NAME)
re : fclean all
