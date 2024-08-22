#ifndef SO_LONG_H
# define SO_LONG_H

#include "libft/libft.h"
#include "mlx-linux/mlx.h"
#include <mlx.h>

#define	WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define SIZE_PIXEL 32


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;



#endif





