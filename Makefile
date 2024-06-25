# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I/usr/include -Imlx

# Library and source settings
NAME = so_long.a
SRC = test.c
OBJDIR = ./obj
OBJS = $(SRC:%.c=$(OBJDIR)/%.o)
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11



# Rule to build object files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

# Rule to build the static library
$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

# Default rule
all: $(NAME)

# Clean up object files and the library
clean:
	rm -rf $(OBJDIR) $(NAME)

.PHONY: all clean
