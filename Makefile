# Contains the X11 and MLX header files
INCLUDES = -I/usr/include -Imlx
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long.a
SRC = test.c
OBJDIR = ./obj
OBJS = $(SRC:%.c=$(OBJDIR)/%.o)
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

 
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
 
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) ar rc $(NAME) $(OBJS) $(MLX_FLAGS)


all:
	$(NAME)