CC = gcc

FLAGS = -Werror -Wextra -Wall -g3  # -fsanitize=address

NAME = libft.a

SOURCES = ft_itoa.c\
		  ft_bzero.c\
		  ft_isalnum.c\
		  ft_isalpha.c\
		  ft_isascii.c\
		  ft_isdigit.c\
		  ft_isprint.c\
		  ft_memccpy.c\
		  ft_memchr.c\
		  ft_memcmp.c\
		  ft_calloc.c\
		  ft_memcpy.c\
		  ft_memmove.c\
		  ft_memset.c\
		  ft_strdup.c\
		  ft_strchr.c\
		  ft_strncmp.c\
		  ft_strjoin.c\
		  ft_strlcat.c\
		  ft_strlen.c\
		  ft_strlcpy.c\
		  ft_strrchr.c\
		  ft_strnstr.c\
		  ft_substr.c\
		  ft_tolower.c\
		  ft_toupper.c\
		  ft_strtrim.c\
		  ft_split.c\
		  ft_strmapi.c\
		  ft_atoi.c\
	      ft_putchar_fd.c\
		  ft_putstr_fd.c\
		  ft_putendl_fd.c\
		  ft_putnbr_fd.c\
		  get_next_line.c\
		  get_next_line_utils.c\
		  strings.c\
		  double_linkedlist.c\
		  double_linkedlist_2.c\

SRCB  =	 ft_lstnew_bonus.c\
		 ft_lstadd_front_bonus.c\
		 ft_lstsize_bonus.c\
		 ft_lstlast_bonus.c\
		 ft_lstadd_back_bonus.c\
		 ft_lstdelone_bonus.c\
		 ft_lstclear_bonus.c\
		 ft_lstiter_bonus.c\
		 ft_lstmap_bonus.c\


HEADERS = libft.h

OBJECT = $(SOURCES:.c=.o)

all : $(NAME) clean 

$(NAME): clean fclean
	@$(CC) $(FLAGS) -c $(SOURCES)
	@ar rc $(NAME) $(OBJECT)
	@ranlib $(NAME)

all: $(NAME)

bonus:
	gcc -Wall -Wextra -Werror -c $(SOURCES) $(SRCB)
	ar -rc $(NAME) *.o
	ranlib $(NAME)
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all banner

master: clean fclean
	@rm -rf $(NAME)
	@echo -e "\033[0;31m  Making the objects of libft *.o      \033[0m"
	$(CC) $(FLAGS) -c $(SOURCES) $(SRCB)
	pwd

.PHONY: clean fclean

