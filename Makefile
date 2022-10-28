
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

LEAKFLAGS	=	-fsanitize=address

INCLDS	=	includes
SRCS	=	$(shell find srcs -iname *.c)
OBJS	=	$(SRCS:.c=.o)

FLAGS	=	-Wall -Wextra -Werror
RLINE	=	-lreadline
RLFLAGS	=	-L /Users/$(USER)/Desktop/homebrew/opt/readline/lib
RDFLAGS	=	-I /Users/$(USER)/Desktop/homebrew/opt/readline/include

NAME	= minishell

LIBDIR	= libft
LIBFT	= $(LIBDIR)/libft.a

all : libft $(NAME)

$(LIBFT) :
	libft

libft :
	make -C $(LIBDIR) all

$(NAME) : $(OBJS)
	@gcc $(FLAGS) $(LIBFT) $(RLINE) $(RDFLAGS) $(RLFLAGS) $(OBJS) -o $(NAME)
	@printf "$(BOLD)$(RED)Creating Executable ----> $(RESET)$(BOLD)$(CYAN) $@ $(END)\n"

clean :
	@make -C $(LIBDIR) clean
	@rm -f $(OBJS)
	@printf "$(BOLD)$(RED)(MINISHELL)	---->	$(RESET)$(BOLD)$(WHITE)Clear$(END)\n"

fclean :
	@make -C $(LIBDIR) fclean
	@rm -f $(OBJS) $(NAME)
	@printf "$(BOLD)$(RED)(MINISHELL)	---->	$(RESET)$(BOLD)$(WHITE)Full Clear$(END)\n"

re : fclean all

%.o : %.c	$(LIBFT)
	@gcc $(FLAGS) $(RDFLAGS) -I $(INCLDS) -c $< -o $@
	@printf "$(CYAN)Creating ----> $(RESET)$(BOLD)$(WHITE) $@ $(END)\n"

.PHONY: clean fclean re all libft