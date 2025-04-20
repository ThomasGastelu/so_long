NAME= so_long

CC= cc
FLAG= -Wall -Werror -Wextra -g3

SRC= utils_player.c player.c mappe.c so_long.c utils/get_next_line.c utils/get_next_line_utils.c utils/map_utils.c parsing/parsing.c parsing/parsing1.c

BIN_PATH=bin/
OBJ=$(addprefix $(BIN_PATH), $(SRC:.c=.o))


LIBFT_DIR=../../cercle_1/libft
LIBFT_LIB=../../cercle_1/libft/libft.a

MLX_DIR= ../../minilibx-linux
MLX_LIB=$(MLX_DIR)/libmlx.a
LIBS= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all:$(NAME)

$(NAME):$(OBJ) $(LIBFT_LIB)
	$(CC) $(FLAG) -o $(NAME) $(OBJ) $(MLX_LIB) $(LIBS) $(LIBFT_LIB)

$(BIN_PATH)%.o:%.c
	mkdir -p $(dir $@)
	$(CC) $(FLAG) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(BIN_PATH)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean:clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
re:fclean all

.PHONY: all clean fclean re