#ifndef SO_LONG_H
# define SO_LONG_H

#include "libft/libft.h"
#include "mlx-linux/mlx.h"
#include <mlx.h>

#define	WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define SIZE_PIXEL 32
#define KEY_ESC 65307


# define UP_KEY				119
# define LEFT_KEY				97
# define DOWN_KEY				115
# define RIGHT_KEY				100


typedef struct	s_data {
	void *mlx;
	void *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_imgs
{
	void *walls;
	void *collectables;
	void *player;
	void *exit;
	void *empty_space;
	int	img_width;
	int	img_height;
}t_imgs;



#endif





