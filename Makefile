# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#              #
#    Updated: 2024/10/20 19:07:49 by ele-borg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

COMMON_FILES = utils_part1.c \
				utils_part2.c \
				utils_part3.c \
				init_part1.c \
				init_part2.c \
				child_creation.c \
				pipe_handle.c \
				execution.c \
				lst_functions_parta.c \
				lst_functions_partb.c \

SRC_FILES = main.c \
			$(COMMON_FILES)

SRC_BONUS_FILES = main_bonus.c \
				$(COMMON_FILES)


OBJ_FILES = $(SRC_FILES:.c=.o)

OBJ_BONUS_FILES = $(SRC_BONUS_FILES:.c=.o)

NAME = pipex

NAME_BONUS = pipex_bonus

FLAGS = -Wall -Wextra -Werror -g3 -I.

CC = cc

#rules

all: ${NAME} 

${NAME}: ${OBJ_FILES}
	${CC} ${FLAGS} ${OBJ_FILES} -o ${NAME}

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS_FILES)
	$(CC) $(FLAGS) $(OBJ_BONUS_FILES) -o $(NAME_BONUS)

%.o: %.c
	$(CC) -c $(FLAGS) $< -o $@

clean: 
	rm  -f ${OBJ_FILES} ${OBJ_BONUS_FILES} 

fclean: clean
	rm -f ${NAME} ${NAME_BONUS}

re: fclean all

reclean : all clean

.PHONY: all clean fclean re bonus