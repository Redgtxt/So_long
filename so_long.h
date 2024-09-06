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

// void	parse_line(char *line, size_t length);
// void	validate_columns(char *line, size_t length);
// void	find_player(char **map, int map_size, size_t length, int *player_x,int *player_y);
// void	flood_fill(char **map, int x, int y, int map_size, size_t length);
// void	check_collectables(char **map, int map_size, size_t length);
// int	count_lines(int fd);
// void read_map(int map_size, int fd, char *line, size_t length_first_line, t_map *vars);
// void pass_map(char *line, size_t length_first_line, t_map *map, int map_size, int fd);
// void running_map(t_map *map,char *path);

// void exit_program(void);
// int check_name (char *path);
// void init_variables(t_data *vars);

//Map Functions
void check_walls(t_map *vars);
void error_message(void);
void check_rectangular(t_map *vars);
int check_name (char *path);
void find_player(t_map *vars, int *player_x, int *player_y);
void check_letters(t_map *vars);


void create_window(t_data *vars,t_map *map);
int	close_window(t_data *vars);
int	key_hook(int keycode, t_data *vars);
void	draw_img(t_data *vars, void *img, int x, int y);
void store_sprites(t_data *vars,t_imgs *sprite);
int draw_map(t_data *vars,t_map *map,t_imgs *sprite);

#endif





