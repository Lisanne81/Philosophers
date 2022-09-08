# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lhoukes <lhoukes@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/22 08:51:43 by lhoukes       #+#    #+#                  #
#    Updated: 2022/08/17 17:43:43 by lhoukes       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_FILES 	=	 ft_strlen.c ft_atoi.c ft_isdigit.c  ft_putchar_fd.c \
					ft_putstr_fd.c ft_putnbr_fd.c ft_split.c ft_strncmp.c \
					ft_itoa.c ft_memset.c ft_strjoin.c ft_bzero.c \
					ft_strdup.c ft_memcpy.c ft_strchr.c ft_strnstr.c

OBJECT_SRC = $(SRC_FILES:.c=.o)

LIBC = ar -rcs
FLAGS = -Wall -Wextra -Werror
HEADER_FILE = libft.h
RM = rm -f

ifdef BONUS
OBJ_FILES = $(OBJECT_SRC) $(OBJECT_BONUS)
else
OBJ_FILES = $(OBJECT_SRC)
endif

all: $(NAME)
$(NAME): $(OBJ_FILES)
			@$(LIBC) $(NAME) $(OBJ_FILES)
			@echo "Hello! Let the magic begin!"
			@echo "First off: the compiling process..."
			@echo "Great Job! That was succesful"
			@echo "Next step: create a library"
			@echo "Succesfully created a library"
			@echo "That was great! Start running those tests!"

%.o: %.c $(HEADER_FILE)
			@$(CC) -c $(FLAGS) -o $@ $<

bonus:
			@$(MAKE) BONUS=1 all
			@echo "Great! Bonus Part(y) Time!"

clean:
			@echo "All done, it's time to 'Marie Kondo' - smile"
			@echo "Remove object files...thank you"
			@$(RM) $(OBJ_FILES) $(OBJECT_BONUS)
			@echo "Deleted!"

fclean:		clean
			@echo "Remove executable..."
			@$(RM) $(NAME)
			@echo "Deleted!"
			@echo "Thank you for taking the time to review my work!"
			@echo "...and remember: Don't Panic... 42 is the answer!"
re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: all clean fclean re
