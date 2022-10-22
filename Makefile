
SRC_DIR	= 	srcs/
OBJ_DIR	= 	objs/
INCLDS	=	includes/

SUBDIRS =	$(addprefix $(OBJ_DIR),$(shell find srcs/ -type d | cut -c 6-))
C_FILES =	$(shell find srcs/ -iname *.c | cut -c 6-)
SRCS	=	$(addprefix $(SRC_DIR),$(C_FILES))
OBJS    =	$(addprefix $(OBJ_DIR),$(C_FILES:.c=.o))

FLAGS	=	-Wall -Wextra -Werror
RLINE	=	-lreadline
RLFLAGS	=	-L /Users/$(USER)/Desktop/homebrew/opt/readline/lib
RDFLAGS	=	-I /Users/$(USER)/Desktop/homebrew/opt/readline/include

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

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(LIBFT)
	gcc -I $(INCLDS) $(FLAGS) $(RDFLAGS) -c $< -o $@

# rule to debug Makefile
print:
	$(info OBJS = $(OBJ))
	$(info only files= $(C_FILES))
	$(info files with path = $(SRCS))
	$(info subdirectories = $(SUBDIRS))

.PHONY: clean fclean re all libft