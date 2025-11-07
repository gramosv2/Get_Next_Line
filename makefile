# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goramos- <goramos-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 01:28:00 by gramos-l          #+#    #+#              #
#    Updated: 2025/11/07 18:32:49 by goramos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= get_next_line.c get_next_line_utils.c

SRCS_BONUS	= get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= get_next_line.a

CC			= gcc
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror

GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

all:		${NAME}

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
			@echo "$(GREEN)Compilado: $<$(RESET)"

${NAME}:	${OBJS}
			@ar rcs ${NAME} ${OBJS}
			@echo "$(GREEN)✓ Librería $(NAME) creada$(RESET)"

bonus:		${OBJS_BONUS}
			@ar rcs ${NAME} ${OBJS_BONUS}
			@echo "$(GREEN)✓ Librería $(NAME) creada con BONUS$(RESET)"

clean:
			@${RM} ${OBJS} ${OBJS_BONUS}
			@echo "$(RED)✗ Objetos eliminados$(RESET)"

fclean:		clean
			@${RM} ${NAME}
			@echo "$(RED)✗ Librería eliminada$(RESET)"

re:			fclean all

.PHONY:		all bonus clean fclean re
