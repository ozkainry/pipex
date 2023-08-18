# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ozozdemi <ozozdemi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 16:40:50 by ozozdemi          #+#    #+#              #
#    Updated: 2023/07/19 16:13:22 by ozozdemi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		pipex
CC =		@cc
CFLAGS =	-Wall -Wextra -Werror -g3
OBJ =		$(patsubst src%, obj%, $(SRC:.c=.o))
SRC =		src/pipex.c \
		src/error.c \
		src/path.c \
		src/free.c \
		src/child.c \

all:		obj ${NAME}

${NAME}:	${OBJ}
		@echo "\033[0;33m\nCOMPILING LIBFT"
		@make -sC libft/
		@echo "\033[1;32mLIBFT COMPILED\n"
		@echo "\033[0;33mCOMPILING PIPEX"
		${CC} -o ${NAME} ${OBJ} libft/libft.a
		@echo "\033[1;32mPIPEX COMPILED\n"

obj:
			@mkdir -p obj

obj/%.o:	src/%.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
		@echo "\033[0;31m\nDELETING OBJ FILES IN LIBFT"
		@make clean -sC libft/
		@rm -rf ${OBJ} obj
		@echo "\033[1;32mDONE\n"

fclean:		clean
		@echo "\033[0;31mDELETING PIPEX EXECUTABLE"
		@rm -rf ${NAME}
		@make fclean -sC libft/
		@echo "\033[1;32mDONE\n"

re:		fclean all

.PHONY:		all clean fclean re