# Nome do compilador
CC = cc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Nome do executável final
NAME = so_long

# Diretório da biblioteca
LIBFT_DIR = libft
MLX_DIR = mlx-linux  # Diretório correto da MiniLibX

# Arquivos de cabeçalho
INCLUDES = -I$(LIBFT_DIR)

# Arquivos fonte e objeto
SRC = test.c
OBJ = $(SRC:.c=.o)

# Nome da biblioteca e caminho
LIBFT = $(LIBFT_DIR)/libft.a

# Alvo padrão
all: $(NAME)

# Compilar o executável
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

# Compilar o objeto
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -I$(MLX_DIR) -O3 -c $< -o $@

# Limpar arquivos objeto
clean:
	rm -f $(OBJ)

# Limpar arquivos objeto e o executável
fclean: clean
	rm -f $(NAME)

# Reconstruir tudo
re: fclean all

# Incluir a biblioteca (compilá-la se necessário)
$(LIBFT):
	make -C $(LIBFT_DIR)

.PHONY: all clean fclean re
