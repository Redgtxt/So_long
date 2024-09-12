#ifndef SO_LONG_H
# define SO_LONG_H

#include "libft/libft.h"
#include "mlx-linux/mlx.h"
#include <mlx.h>

#define	WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define SIZE_PIXEL 32
#define KEY_ESC 65307


# define UP_KEY					119
# define LEFT_KEY				97
# define DOWN_KEY				115
# define RIGHT_KEY				100


typedef struct s_map
{
	char **matrix;
	int	map_width;
	int	map_height;
	int rows;
	int column;

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
	void *escape;
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
	t_player_info player_info;
	t_map	map;
	t_imgs	sprites;
}				t_data;


//Map Functions
int	read_map(char *path, t_map *vars);
int	build_matrix(char *map, t_map *vars);
void check_walls(t_map *vars);
void error_message(void);
void check_rectangular(t_map *vars);
int check_name (char *path);
int	ft_strlen_no_newline(char *string);
void find_player(t_map *vars, int *player_x, int *player_y);
void flood_fill(char **matrix_copy, int x, int y, int rows, int columns, int *found_exit, int *collectibles);
void check_letters(t_map *vars);

char **copy_matrix(t_map *vars);
void free_matrix(char **matrix, int rows);


void create_window(t_data *vars,t_map *map);
int	close_window(t_data *vars);
int	key_hook(int keycode, t_data *vars);
void	draw_img(t_data *vars, void *img, int x, int y);
void store_sprites(t_data *vars,t_imgs *sprite);
void draw_map(t_data *vars, t_map *map, t_imgs *sprite);

#endif





