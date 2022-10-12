SRCS	=	srcs/main.c					\
			srcs/parsing_print.c		\
			srcs/parsing_free.c			\
			srcs/parsing_env.c			\
			srcs/parsing_cmd.c			\
			srcs/parsing_init.c			\
			srcs/parsing_arg.c			\
			srcs/parsing_red.c			\
			srcs/parsing_var.c			\
			srcs/parsing_red2.c			\
			srcs/parsing_quotes.c		\
			srcs/parsing_char_utils.c	\
			srcs/parsing_index_utils.c	\
			srcs/ft_exit.c				\
			srcs/ft_echo.c				\
			srcs/ft_export.c			\
			srcs/ft_unset.c				\
			srcs/ft_env.c				\
			srcs/ft_pwd.c				\
			srcs/ft_cd.c				

INCLDS	= ./includes/minishell.h
OBJS    = $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror
RLINE	= -lreadline
RLFLAGS	=	-L /Users/abouchet/Desktop/homebrew/opt/readline/lib
RDFLAGS	=	-I /Users/abouchet/Desktop/homebrew/opt/readline/include

NAME	= minishell

LIBDIR	= ./libft
LIBFT	= $(LIBDIR)/libft.a

all : libft $(NAME)

libft :
	make -C $(LIBDIR) all

$(NAME) : $(OBJS)
	gcc $(FLAGS) $(LIBFT) $(RLINE) $(RDFLAGS) $(RLFLAGS) $(OBJS) -o $(NAME)

clean :
	make -C $(LIBDIR) fclean
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

%.o : %.c $(INCLDS) $(LIBFT)
	gcc $(FLAGS) $(RDFLAGS) -c $< -o $@

.PHONY: clean fclean re all libft