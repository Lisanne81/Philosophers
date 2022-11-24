NAME		 	= philo
#-------------------------------------------#
LIBFT			= libft/libft.a
HEADER_M		= includes/philosophers.h
#-------------------------------------------#
SRC				= main.c terminal_image.c init_philosophers.c \
					error_check.c thread.c
DIR_OBJ			= ./obj
OBJS 			= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o)) #$(SRC:.c=.o)
#-------------------------------------------#
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -g
#-------------------------------------------#
BLUE			=	\033[38;5;30m
GREEN			= 	\033[38;5;43m
RED				=	\033[38;5;124m
PINK			= 	\033[38;5;167m
ORANGE			=	\033[38;5;208m
NO_COLOR		=	\033[0m
#-------------------------------------------#

all: $(LIBFT) $(NAME) $(HEADER)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(LIBFT) $(NAME) $(HEADER)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(DIR_OBJ)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) -o $@ -c $< $(CFLAGS)

$(LIBFT):
		printf "\033c"
		@echo "☝️ $(BLUE)First of: Make LIBFT$(NO_COLOR) 📖"
		@$(MAKE) -C./libft

clean:
	rm -rf $(DIR_OBJ) res subject
	$(MAKE) clean -C ./libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all
