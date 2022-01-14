SRCS		= ${wildcard *.c}
OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

LIBFT_DIR_THOMAS	= libft_thomas
LIBFT_A_THOMAS		= libft_thomas.a
LIBFT_THOMAS		= -L. -lft_thomas

LIBFT_DIR_ADRIEN	= libft_adrien
LIBFT_A_ADRIEN		= libft_adrien.a
LIBFT_ADRIEN		= -L. -lft_adrien

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR_THOMAS}/
			cp ${LIBFT_DIR_THOMAS}/$(LIBFT_A_THOMAS) .
			make --silent -C ${LIBFT_DIR_ADRIEN}/
			cp ${LIBFT_DIR_ADRIEN}/$(LIBFT_A_ADRIEN) .
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIBFT_THOMAS) $(LIBFT_ADRIEN)

clean:
			${RM} ${OBJS}
			make --silent -C ${LIBFT_DIR_THOMAS} clean
			make --silent -C ${LIBFT_DIR_ADRIEN} clean

fclean:		clean
			${RM} ${NAME}
			${RM} ${LIBFT_A_THOMAS}
			${RM} ${LIBFT_A_ADRIEN}
			${RM} ${LIBFT_DIR_THOMAS}/${LIBFT_A_THOMAS}
			${RM} ${LIBFT_DIR_ADRIEN}/${LIBFT_A_ADRIEN}

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run
