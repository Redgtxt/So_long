/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:37:34 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "mlx-linux/mlx.h"

# define SIZE_PIXEL 32
# define KEY_ESC 65307

# define UP_KEY 119
# define LEFT_KEY 97
# define DOWN_KEY 115
# define RIGHT_KEY 100

/* Width in pixels of the move counter drawn in the top-left corner. */
# define COUNTER_WIDTH 160

typedef struct s_map
{
	char			**matrix;
	int				map_width;
	int				map_height;
	int				rows;
	int				column;
	int				exit_x;
	int				exit_y;
}					t_map;

typedef struct s_flood_fill
{
	char			**matrix_copy;
	int				*stack;
	int				top;
	int				rows;
	int				columns;
	int				found_exit;
	int				collectibles;
}					t_flood_fill;

typedef struct s_player
{
	int				p_x;
	int				p_y;
	int				total_collectables;
	int				move_count;
}					t_player;

typedef struct s_imgs
{
	void			*walls;
	void			*collectables;
	void			*player;
	void			*escape;
	void			*escape_open;
	void			*empty_space;
}					t_imgs;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	t_player		player;
	t_map			map;
	t_imgs			sprites;
}					t_data;

// Map loading and validation
void				check_name(char *path, t_data *vars);
int					read_map(char *file, t_data *vars);
int					build_matrix(char *file, t_data *vars);
char				**copy_matrix(t_data *vars);
void				free_matrix(char **matrix, int rows);
int					ft_strlen_no_newline(char *string);
void				check_rectangular(t_data *vars);
void				check_walls(t_data *vars);
void				check_letters(t_data *vars);
void				check_conditions(t_data *vars);
void				count_map_elements(t_data *vars, int *c_count, int *p_count,
						int *exit_count);
void				find_tile(t_data *vars, char tile, int *x, int *y);
int					count_collectibles(t_data *vars);
void				check_path_player_to(t_data *vars);
void				flood_fill(t_flood_fill *fill, int x, int y);
void				init_variables(t_data *vars);

// Window and drawing
void				create_window(t_data *vars);
void				store_sprites(t_data *vars);
void				draw_img(t_data *vars, void *img, int x, int y);
void				draw_tile(t_data *vars, int x, int y);
void				draw_exit(t_data *vars, int x, int y);
int					draw_map(t_data *vars);
void				draw_counter(t_data *vars);

// Gameplay
int					key_hook(int keycode, t_data *vars);
void				move_player(t_data *vars, int x_offset, int y_offset);
void				display_moves(t_data *vars);

// Errors and cleanup
void				error_message(t_data *vars, char *reason);
void				cleanup(t_data *vars);
int					close_window(t_data *vars);

#endif
