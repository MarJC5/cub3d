# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m

##################################################
## 			MINILIBX MAIN VERSION 				##
##################################################
SRCS_DIR	= ./src/
SRCS_FILES	=  main.c
SRCS_FILES	+= 	pars_utils.c \
				pars_check.c \
				read_map.c \
				error_utils.c \
				free_stuff.c \
				minilibft.c

SRCS		:= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

O_DIR		= ./objs/
D_DIR		= ./debugs/
HEADS		= -I./includes/ -I./libft -I./mlx

OBJS_FILES	:= ${SRCS_FILES:.c=.o}
OBJS		:= ${patsubst %, ${O_DIR}%, ${OBJS_FILES}}
DEBUGS		:= ${patsubst %, ${D_DIR}%, ${OBJS_FILES}}

VALGRIND	= valgrind  --main-stacksize=167104768 --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=memcheckignore --gen-suppressions=yes
VALGRIND	= valgrind  --suppressions=memcheckignore --gen-suppressions=yes

LIBFT		= ./libft
MAKELIB		= ${MAKE} -C ${LIBFT}
OBJS		+= ${LIBFT}/libft.a
DEBUGS		+= ${LIBFT}/libft.a

UNAME_S 	:= $(shell uname -s)
ifeq (${UNAME_S},Linux)
LIBX		= ./mlx-linux
else
LIBX		= ./mlx
endif
MAKELIBX	= ${MAKE} -C ${LIBX}
OBJS		+= ${LIBX}/libmlx.a
DEBUGS		+= ${LIBX}/libmlx.a

LIBS		= -framework OpenGL -framework AppKit

NAME		= cub3D
ifeq (${OS},Windows_NT)
	NAME	:= ${NAME:=.exe}
endif

CC			= cc
AR			= ar rcs
MKDIR		= mkdir
CP			= cp -f
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror
# Add this for debug
CFLAGS		+= -g3

all:	${NAME}

#Compile normal executable
${NAME}: ${O_DIR} ${OBJS}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

#Create objects directory
${O_DIR}:
	${MKDIR} ${O_DIR}

#Compile normals objects
${O_DIR}%.o: ${SRCS_DIR}%.c
	${CC} ${CFLAGS} ${HEADS} -o $@ -c $<

#Compile libft
${LIBFT}/libft.a:
	${MAKELIB} all

#Compile minilibx
${LIBX}/libmlx.a:
	${MAKELIBX} all

#Compile and use valgrind
valgrind:
	valgrind --leak-check=full ./$(NAME) ./maps/demo.cub

#Compile a debug executable with -g and fsanitize
debug: ${D_DIR} ${DEBUGS}
	${MAKELIB} all
	${MAKELIBX} all
	${CC} ${CFLAGS} -fsanitize=address -o ${NAME} ${DEBUGS} ${LIBS}

#Create debug directory
${D_DIR}:
	${MKDIR} ${D_DIR}

#Compile debug objects
${D_DIR}%.o: ${SRCS_DIR}%.c
	${CC} ${CFLAGS} -g ${HEADS} -o $@ -c $<

clean:
	@${RM} ${OBJS} ${OBJSB} ${DEBUGS}
	@${RM} -r ${O_DIR}
	@${RM} -r ${D_DIR}
	@${MAKELIB} clean
	@echo "[$(ORANGE)libft$(RESET)] clean *.o files : $(GREEN)OK$(RESET)"
	@echo "[$(ORANGE)$(NAME)$(RESET)] clean *.o files : $(GREEN)OK$(RESET)"

fclean:	clean
	@${RM} ${NAME}
	@${RM} -r ${NAME}.dSYM
	@${MAKELIB} fclean
	@${RM} -r ${NAME}.dSYM
	@echo "[$(ORANGE)libft$(RESET)] fclean : $(GREEN)OK$(RESET)"
	@echo "[$(ORANGE)$(NAME)$(RESET)] fclean: $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) has been clean up"

leaks:
	leaks -atExit -- ./$(NAME) ./maps/demo.cub

re:			fclean all

.PHONY:		all clean fclean re debug valgrind leaks