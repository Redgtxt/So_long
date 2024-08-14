# Nome do compilador
CC = cc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Nome do executável final
NAME = so_long

# Diretório da biblioteca
LIBFT_DIR = libft

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
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compilar o objeto
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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
