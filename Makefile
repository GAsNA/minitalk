### Variables

LIBFT_PATH	=	./librairies/Libft/
LIBFT		=	${LIBFT_PATH}libft.a

SRCS_S		=	server.c
SRCS_C		=	client.c

OBJS_S		=	${SRCS_S:.c=.o}
OBJS_C		=	${SRCS_C:.c=.o}

HEADERS_PATH	=	./headers/
HEADER		=	${HEADERS_PATH}minitalk.h

SERVER		=	server
CLIENT		=	client

CC		=	clang
RM		=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror


### Commandes

all:		${SERVER} ${CLIENT}

${SERVER}:	${OBJS_S} ${LIBFT}
		${CC} ${CFLAGS} ${OBJS_S} ${LIBFT} -o ${SERVER}

${CLIENT}:	${OBJS_C} ${LIBFT}
		${CC} ${CFLAGS} ${OBJS_C} ${LIBFT} -o ${CLIENT}

.c.o:
		${CC} -c ${CFLAGS} -I${HEADER} $^ -o $@

${LIBFT}:
		make -C ${LIBFT_PATH}

clean:
		make -C ${LIBFT_PATH} clean
		${RM} ${OBJS_S}
		${RM} ${OBJS_C}

fclean:		clean
		make -C ${LIBFT_PATH} fclean
		${RM} ${SERVER}
		${RM} ${CLIENT}

re:		fclean all

.PHONY:		all clean fclean re
