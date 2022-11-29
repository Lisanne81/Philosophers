NAME		 	= philo
#-------------------------------------------#
HEADER_M		= includes/philosophers.h
#-------------------------------------------#
SRC				= main.c init_philosophers.c \
					error_check.c check_input.c \
					utils.c time.c thread.c actions.c
DIR_OBJ			= ./obj
OBJS 			= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o)) #$(SRC:.c=.o)
#-------------------------------------------#
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra -g #-fsanitize=address
#-------------------------------------------#
BLUE			=	\033[38;5;30m
GREEN			= 	\033[38;5;43m
RED				=	\033[38;5;124m
PINK			= 	\033[38;5;167m
ORANGE			=	\033[38;5;208m
NO_COLOR		=	\033[0m
#-------------------------------------------#

all:  $(NAME) $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:  start $(NAME) $(HEADER)

start:	
		@echo "$(ORANGE)       Let's run:$(NO_COLOR)"
		@echo "      ▄▀▄     ▄▀▄"
		@echo "     ▄█░░▀▀▀▀▀░░█▄"
		@echo " ▄▄  █░░░░░░░░░░░█  ▄▄"
		@echo "█▄▄█─█░░▀░░┬░░▀░░█─█▄▄█"
		@echo "$(PINK)🅿 🅷 🅸 🅻 🅾 🆂 🅾 🅿 🅷 🅴 🆁 🆂"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(DIR_OBJ)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(DIR_OBJ) res subject

fclean: clean
	rm -f $(NAME)

re: fclean all
