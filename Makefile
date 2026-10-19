# Nome do compilador
CC = cc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Nome do executável final
NAME = so_long

# Diretórios das bibliotecas
# (os comentários ficam em linhas próprias: um comentário no fim da linha
# deixa espaços no valor da variável)
LIBFT_DIR = libft
MLX_DIR = mlx-linux

# Arquivos de cabeçalho
INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)

# Arquivos fonte e objeto
SRC = gameplay.c draw.c new_map.c map_utils.c map_letters.c so_long.c \
	clean.c init_stuff.c window.c
OBJ = $(SRC:.c=.o)

# Nome das bibliotecas e caminhos
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a
MLXFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11

# Alvo padrão
all: $(NAME)

# Compilar o executável
$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft $(MLXFLAGS) -lm -lz -o $(NAME)

# Compilar o objeto
%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

# Incluir as bibliotecas (compilá-las se necessário)
$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

# Limpar arquivos objeto
clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

# Limpar arquivos objeto e o executável
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Reconstruir tudo
re: fclean all

.PHONY: all clean fclean re
