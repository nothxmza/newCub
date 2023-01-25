# **************************************************************************** #
# VARIABLES

NAME				:= cub3D

CC					:= gcc
CFLAGS				:= #-Wall -Wextra -Werror
RM					:= rm -rf
INCS				:= -I ./includes/

LIBFT				:= libft
LIBFT_A				:= ./libft/libft.a

MLX_DIR				:= mlx
MLX_A				:= ./mlx/libmlx.a

SRC_DIR				:= ./srcs/
OBJ_DIR				:= ./obj/

SRC_FILES			:=	main.c \
						parsing.c \
						init.c \
						save_texture.c \
						save_color.c \
						exit.c \
						utils.c \
						read_file.c \
						parser_map.c \
						start_game.c \
						close.c \
						key.c \

OBJ_FILES			:= ${SRC_FILES:.c=.o}
SRC					:= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ					:= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

all : $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	make -C $(MLX_DIR)
	make -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -I . $(MLX_A) $(LIBFT_A) -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS)  -c $< -o $@ $(INCS)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)
	make fclean -C $(LIBFT)

re: fclean all
.PHONY: all clean fclean re