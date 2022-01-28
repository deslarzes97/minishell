SRCS		= 	srcs/main.c 		\
				srcs/prompt.c		\
				srcs/builtins_1.c	\
				srcs/builtins_2.c	\
				srcs/echo.c			\
							srcs/ls_provisoire.c	\


OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -g -Wall -Wextra -Werror
NAME		= minishell
RM			= rm -f

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L./libft -lft

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make --silent -C ${LIBFT_DIR}/
			$(CC) $(CFLAGS) -o $(NAME) ${OBJS} $(LIBFT)

clean:
			${RM} ${OBJS}
			make --silent -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			make --silent -C ${LIBFT_DIR} fclean

re:			fclean all

run:		
			./${NAME}

.PHONY:		all clean fclean re run

#-------HELP TO DEBUG---------#

#-g -fsanitize=address à ajouter lors de la compliation pour le débegueur vscode.
#leaks -atExit -- commande (mac) qui permet de checker si il y'a des leaks.
