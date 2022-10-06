SRCS	=	srcs/main.c

INCLDS	= ./includes/minishell.h
OBJS    = $(SRCS:.c=.o)
FLAGS	= -Wall -Wextra -Werror
RLINE	= -lreadline
NAME	= minishell

LIBDIR	= ./libft
LIBFT	= $(LIBDIR)/libft.a

all : libft $(NAME)

libft : 
	make -C $(LIBDIR) all

$(NAME) : $(OBJS)
	gcc $(FLAGS) $(LIBFT) $(RLINE) $(OBJS) -o $(NAME)

clean :
	make -C $(LIBDIR) fclean
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

%.o : %.c $(INCLDS) $(LIBFT)
	gcc $(FLAGS) -c $< -o $@

.PHONY: clean fclean re all libft