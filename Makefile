NAME 		:= miniRT

OS			:= $(shell uname -s)

SRC_FILES	:= main.c\
				setup_scene.c\
				print_scene.c\
				init.c\
				hooks.c\
				parse/parse_geometry.c\
				parse/parse_scene.c\
				parse/parse_utils.c\
				parse/parse_utils_2.c\
				parse/parse_check.c\
				parse/parse_check_2.c\
				parse/parse_check_3.c\
				resize_geometry/resize_geometry.c\
				resize_geometry/resize_utils.c\
				sphere.c\
				vec_operations.c\
				vec_operations_2.c\
				vec_operations_3.c\
				ray_launcher.c\
				plane.c\
				cylinder.c

OBJ_FILES	:= $(patsubst %.c,%.o,$(SRC_FILES))
HDR_FILES	:= miniRT.h\
				scene.h\
				debug.h\
				parse.h\

LIB_FILES	:= libft/libft.a\
				MLX42/build/libmlx42.a

SRC_DIR		:= ./srcs/
SRC_SUBDIRS	:= parse/ resize_geometry/
OBJ_DIR		:= ./obj/
OBJ_SUBDIRS := $(SRC_SUBDIRS)
HDR_DIR		:= ./inc/
LIB_DIR		:= ./lib/

CFLAGS		+= -Wall -Wextra -Werror -I$(LIB_DIR)libft/ -I$(LIB_DIR)MLX42/include/MLX42 -I$(HDR_DIR) -g -fsanitize=address

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJ_FILES)) $(addprefix $(LIB_DIR),$(LIB_FILES))
	@$(CC) $(CFLAGS) $^ -Iinclude -ldl -lglfw -pthread -lm -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(HDR_DIR),$(HDR_FILES))
	@mkdir -p $(addprefix $(OBJ_DIR),$(OBJ_SUBDIRS))
	@$(CC) $(CFLAGS) $< -c -o $@

$(LIB_DIR)libft/libft.a:
	@$(MAKE) -j --directory=$(LIB_DIR)libft/ bonus

$(LIB_DIR)MLX42/build/libmlx42.a:
	cmake -S ./lib/MLX42 -B ./lib/MLX42/build
	cmake --build ./lib/MLX42/build -j4

clean:
	@$(MAKE) -j --directory=$(LIB_DIR)libft/ fclean
	cmake --build ./lib/MLX42/build --target clean
	@rm -f $(addprefix $(OBJ_DIR),$(OBJ_FILES))

fclean: clean
	@rm -f $(NAME)

re: fclean all
