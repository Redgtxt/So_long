/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:37:34 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/14 14:37:36 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx-linux/mlx.h"
# include <mlx.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define SIZE_PIXEL 32
# define KEY_ESC 65307

# define UP_KEY 119
# define LEFT_KEY 97
# define DOWN_KEY 115
# define RIGHT_KEY 100

typedef struct s_map
{
	char			**matrix;
	int				map_width;
	int				map_height;
	int				rows;
	int				column;

}					t_map;

typedef struct s_flood_fill
{
	char			**matrix_copy;
	int				rows;
	int				columns;
	int				found_exit;
	int				collectibles;
}					t_flood_fill;

typedef struct s_player_info
{
	int				player_xstart;
	int				player_ystart;
	int				total_collectables;
	int				move_count;
	int				exit_map_available;
}					t_player_info;

typedef struct s_imgs
{
	void			*walls;
	void			*collectables;
	void			*player;
	void			*escape;
	void			*escape_open;
	void			*empty_space;
	int				img_width;
	int				img_height;
}					t_imgs;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				window_width;
	int				window_height;
	t_player_info	player_info;
	t_map			map;
	t_imgs			sprites;
}					t_data;

// Map Functions
int					build_matrix(char *file, t_data *vars);
void				check_walls(t_data *vars);
void				check_rectangular(t_data *vars);
int					read_map(char *file, t_data *vars);
char				**copy_matrix(t_data *vars);
void				free_matrix(char **matrix, int rows);
void				error_message(t_data *vars);
int					check_name(char *path, t_data *vars);
int					ft_strlen_no_newline(char *string);
void				find_player(t_data *vars);
int					count_collectibles(t_data *vars);
void				check_conditions(t_data *vars);
void				flood_fill(t_flood_fill *fill, int x, int y);
void				check_path_player_to(t_data *vars);
void				check_letters(t_data *vars);

int					close_window(t_data *vars);
void				create_window(t_data *vars);
int					key_hook(int keycode, t_data *vars);
void				store_sprites(t_data *vars);
void				draw_img(t_data *vars, void *img, int x, int y);
void				draw_tile(t_data *vars, int x, int y);
void				draw_exit(t_data *vars, int x, int y);
void				draw_map(t_data *vars);
void				draw_exit(t_data *vars, int x, int y);
void				free_error(t_data *vars);
void				display_moves(t_data *vars);
void				count_map_elements(t_data *vars, int *c_count, int *p_count,
						int *exit_count);
void				move_player(t_data *vars, int x_offset, int y_offset);

void				init_variables(t_data *vars);
void				destroy_sprites(t_data *vars);
void				cleanup(t_data *vars);

#endif
