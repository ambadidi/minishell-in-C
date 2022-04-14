CC = gcc
CFLAGS = -Wall -Werror -Wextra


LDFLAGS="-L/Users/abadidi/.brew/opt/readline/lib"
CPPFLAGS="-I/Users/abadidi/.brew/opt/readline/include"

SRC = srcs/compile.c\
		srcs/minishell.c\
		srcs/signal.c\

EXEC = execution/excution_utils.c\
		execution/excution_utils2.c\
		execution/execute_cmd.c\
		execution/fork.c\
		execution/forks_tools.c\
		execution/forks_tools2.c\
		execution/forks_tools3.c\
		execution/here_doc.c\

LEX = lexer/lexer_chech.c\
		lexer/lexer_errors.c\
		lexer/lexer.c\
		lexer/lexter_utills1.c\
		lexer/lexter_utills2.c\
		lexer/lexter_utills3.c\

PARS = parser/arguments.c\
		parser/comand_table.c \
		parser/expander.c \
		parser/parcer_utills3.c  \
		parser/parcer_utils2.c  \
		parser/parser_tools.c   \
		parser/semicolon.c\
		parser/cmd_table_start.c   \
		parser/env.c       \
		parser/files.c  \
		parser/parcer_utils.c \
		parser/parse_map.c \
		parser/redirection.c \
		parser/tokken.c\

BUILTIN = builtins/cd.c \
		builtins/echo.c \
		builtins/exit.c \
		builtins/export_utills.c\
		builtins/pwd.c \
		builtins/cd_utils.c \
		builtins/env.c \
		builtins/export.c \
		builtins/export_utills2.c \
		builtins/unset.c \

OBJ = $(SRC:.c=.o)
NAME = minishell
INC = include/*.h
EXTRALIBFT = libft/libft.a
#
READLINE =   -lreadline -L /Users/abadidi/goinfre/abadidi/.brew/opt/readline/lib -I/Users/abadidi/goinfre/abadidi/.brew/opt/readline/include -lreadline
all: $(NAME)

$(NAME):  $(EXTRALIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LEX) $(PARS) $(EXEC) $(EXTRALIBFT) $(BUILTIN) $(READLINE)
$(EXTRALIBFT):
	make all -C libft/
clean:
	rm -rf $(OBJ) 
	
fclean:
	make fclean -C libft/
	rm -rf $(OBJ) $(NAME)

run:
	@./$(EXEC)
re :
	rm -f log
	rm -rf libft/libft.a
	rm -rf minishell
	make
	make clean -C libft/
