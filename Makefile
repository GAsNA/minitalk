####### DESIGN #######

# Style de typo :
_FIN            =   \033[0m
_GRAS           =   \033[1m
_ITA            =   \033[3m
_SOUS           =   \033[4m
_CLIGN          =   \033[5m
_REV            =   \033[7m

# Couleurs des lettres :
_GRIS           =   \033[30m
_ROUGE          =   \033[31m
_VERT           =   \033[32m
_JAUNE          =   \033[33m
_BLEU           =   \033[34m
_VIOLET         =   \033[35m
_CYAN           =   \033[36m
_BLANC          =   \033[37m

# Couleurs de fonds :
_IGRIS          =   \033[40m
_IROUGE         =   \033[41m
_IVERT          =   \033[42m
_IJAUNE         =   \033[43m
_IBLEU          =   \033[44m
_IVIOLET        =   \033[45m
_ICYAN          =   \033[46m
_IBLANC         =   \033[47m

# Appel
_VALID			=	/bin/echo -e "${_JAUNE}\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\#\n\
				${_VERT}${_IVIOLET}\#\# $1${_FIN}"

CREATED_BIN		=	@$(call _VALID,"Binary created!")
CREATED_LIBFT	=	@$(call _VALID,"Libft library created!")
DELETED_OBJS	=	@$(call _VALID,"Objs deleted!")
DELETED_BIN		=	@$(call _VALID,"Binary deleted!")

####### MAKEFILE #######

### Variables

LIBFT_PATH		=	./librairies/Libft/
LIBFT			=	${LIBFT_PATH}libft.a

SRCS_S			=	server.c
SRCS_C			=	client.c

OBJS_S			=	${SRCS_S:.c=.o}
OBJS_C			=	${SRCS_C:.c=.o}

HEADERS_PATH	=	./headers/
HEADER			=	${HEADERS_PATH}minitalk.h

SERVER			=	server
CLIENT			=	client

CC				=	clang
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror


### Commandes

all:			${SERVER} ${CLIENT}

${SERVER}:		${OBJS_S} ${LIBFT}
				${CC} ${CFLAGS} ${OBJS_S} ${LIBFT} -o ${SERVER}
				${CREATED_BIN}

${CLIENT}:		${OBJS_C} ${LIBFT}
				${CC} ${CFLAGS} ${OBJS_C} ${LIBFT} -o ${CLIENT}
				${CREATED_BIN}

.c.o:
				${CC} -c ${CFLAGS} -I${HEADER} $^ -o $@

${LIBFT}:
				make -C ${LIBFT_PATH}
				${CREATED_LIBFT}

clean:
				make -C ${LIBFT_PATH} clean
				${RM} ${OBJS_S}
				${RM} ${OBJS_C}
				${DELETED_OBJS}

fclean:			clean
				make -C ${LIBFT_PATH} fclean
				${RM} ${SERVER}
				${RM} ${CLIENT}
				${DELETED_BIN}

re	:			fclean all

.PHONY:			all clean fclean re
