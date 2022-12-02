NAME		 	= philo
#-------------------------------------------#
HEADER_M		= includes/philosophers.h
#-------------------------------------------#
SRC				= src/main.c src/init_philosophers.c \
					src/error_check.c src/check_input.c \
					src/time.c src/thread.c src/dinner_time.c \
					src/clean_up_and_free.c src/status_report.c \
					src/wait_your_turn.c
DIR_OBJ			= ./obj
OBJS 			= $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
#-------------------------------------------#
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Werror -Wextra 
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
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(DIR_OBJ)/%.o: %.c
		@mkdir -p $(@D)
		@$(CC) -o $@ -c $< $(CFLAGS)

clean:
		@echo "$(BLUE)🅣 🅗 🅐 🅝 🅚  🅨 🅞 🅤"
		@rm -rf $(DIR_OBJ) res subject

fclean: clean
		@echo "$(GREEN)Sweep sweep 🧹 all clean$(NO_COLOR)"
		@rm -f $(NAME)

re: fclean all
