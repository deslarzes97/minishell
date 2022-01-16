SRCS		= ${wildcard *.c}
OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= pipex
RM			= rm -f

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIB			= -L. -lft

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIB)
			make clean

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run

