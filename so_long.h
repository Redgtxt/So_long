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


typedef struct s_map
{
	char **matrix;
	int	map_width;
	int	map_height;

} t_map;


typedef struct s_player_info
{
	int player_xstart;
	int player_ystart;
}	t_player_info;


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


typedef struct	s_data {
	void *mlx;
	void *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		window_width;
	int		window_height;
}				t_data;

void exit_program(void);
int check_name (char *path);
void init_variables(t_data vars);

void create_window(t_data *vars,t_map *map);
int	close_window(t_data *vars);
int	key_hook(int keycode, t_data *vars);

#endif





