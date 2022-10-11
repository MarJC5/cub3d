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
SRCS_FILES	+= 	key_actions.c \
				info.c \
				move.c \
				move_2.c \
				mouse.c \
				pars_check.c \
				pars_utils.c \
				read_map_utils.c \
				read_map.c \
				error_utils.c \
				free.c \
				minilibft.c \
				shape.c \
				ray.c \
				rays.c \
				rays_h.c \
				rays_v.c \
				raycasting.c \
				render.c \
				check_map.c \
				init.c \
				init_utils.c \
				collision.c \
				utils.c \
				pixel_art.c \
				start.c \
				draw.c \
				init_textures.c \
				animation.c \
				weapon.c \
				audio.c \
				action.c \

SRCS		:= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

UNAME_S 	:= $(shell uname -s)

LIBFT		= ./libft
MAKELIB		= ${MAKE} -C ${LIBFT}

ifeq (${UNAME_S}, Darwin)
	LIBX		= ./mlx
else
	LIBX		= ./mlx-linux
endif
MAKELIBX	= ${MAKE} -C ${LIBX}

O_DIR		= ./objs/
D_DIR		= ./debugs/

OBJS_FILES	:= ${SRCS_FILES:.c=.o}
OBJS		:= ${patsubst %, ${O_DIR}%, ${OBJS_FILES}}
DEBUGS		:= ${patsubst %, ${D_DIR}%, ${OBJS_FILES}}

OBJS		+= ${LIBFT}/libft.a
DEBUGS		+= ${LIBFT}/libft.a
OBJS		+= ${LIBX}/libmlx.a
DEBUGS		+= ${LIBX}/libmlx.a

HEADS		= -I./inc/ -I${LIBFT} -I${LIBX}

ifeq ($(UNAME_S), Darwin)
	LIBS		= -Lmlx -lmlx -lz -framework OpenGL -framework AppKit
else
	LIBS		= -lm -lbsd -lX11 -lXext
endif

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
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

#Create objects directory
${O_DIR}:
	@${MKDIR} ${O_DIR}

#Compile normals objects
${O_DIR}%.o: ${SRCS_DIR}%.c
	@${CC} ${CFLAGS} ${HEADS} -o $@ -c $<

#Compile libft
${LIBFT}/libft.a:
	@${MAKELIB} all

#Compile minilibx
${LIBX}/libmlx.a:
	@${MAKELIBX} all

run: all
	./$(NAME) ./maps/lab.cub

#Compile and use valgrind
valgrind:
	valgrind --leak-check=full --track-origins=yes ./$(NAME) ./maps/demo.cub

#Compile a debug executable with -g and fsanitize
debug: ${D_DIR} ${DEBUGS}
	@${MAKELIB} all
	@${MAKELIBX} all
	@${CC} ${CFLAGS} -fsanitize=address -o ${NAME} ${DEBUGS} ${LIBS}
	@./$(NAME) ./maps/demo.cub

#Create debug directory
${D_DIR}:
	${MKDIR} ${D_DIR}

#Compile debug objects
${D_DIR}%.o: ${SRCS_DIR}%.c
	@${CC} ${CFLAGS} -g ${HEADS} -o $@ -c $<

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
	leaks -atExit -- ./$(NAME) ./maps/lab.cub

maze: all
	@${RM} -r ./maps/maze.cub
	python ./maze/maze_map.py
	./$(NAME) ./maps/maze.cub

re:			fclean all

.PHONY:		all clean fclean re debug valgrind leaks maze run