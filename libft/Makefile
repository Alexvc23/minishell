RESET	= 	\033[0;0m
ERASE	=	\033[2K\r
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PINK	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
END		=	\033[0m
CENTER	=	\033[60G

SOURCES	=	./ft_isalpha.c ./ft_isdigit.c ./ft_isalnum.c ./ft_isascii.c 	\
			./ft_isprint.c ./ft_strlen.c ./ft_memset.c ./ft_bzero.c			\
			./ft_memcpy.c ./ft_memmove.c ./ft_strlcpy.c ./ft_strlcat.c		\
			./ft_toupper.c ./ft_tolower.c ./ft_strchr.c ./ft_strrchr.c		\
			./ft_strncmp.c ./ft_memchr.c ./ft_memcmp.c ./ft_strnstr.c		\
			./ft_atoi.c ./ft_calloc.c ./ft_strdup.c ./ft_substr.c			\
			./ft_strjoin.c ./ft_strtrim.c ./ft_split.c ./ft_itoa.c			\
			./ft_strmapi.c ./ft_striteri.c ./ft_putchar_fd.c				\
			./ft_putstr_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c				\
			./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c ./ft_lstlast.c	\
			./ft_lstadd_back.c ./ft_lstdelone.c ./ft_lstclear.c				\
			./ft_lstiter.c ./ft_lstmap.c									\
			./ft_atoi_base.c												\
			./get_next_line.c ./get_next_line_bonus.c ./get_next_line_utils.c
OBJECTS	=	$(SOURCES:.c=.o)
FLAGS	=	-Wall -Wextra -Werror
NAME	=	libft.a

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@printf "$(BOLD)$(RED)Creating Library ----> $(BOLD)$(CYAN) $@ $(END)\n"


clean:
	@rm -f $(OBJECTS)
	@printf "$(BOLD)$(RED)(LIBFT)		---->	$(RESET)$(BOLD)$(WHITE)Clear$(END)\n"

fclean:
	@rm -f $(OBJECTS) $(NAME)
	@printf "$(BOLD)$(RED)(LIBFT)		---->	$(RESET)$(BOLD)$(WHITE)Full Clear$(END)\n"

re:
	make fclean
	make all

%.o: %.c	libft.h
	@gcc $(FLAGS) -c $< -o $@
	@printf "$(CYAN)Creating ----> $(RESET)$(BOLD)$(WHITE) $@ $(END)\n"

.PHONY: clean fclean re all
