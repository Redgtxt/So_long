#include "so_long.h"

int	close_window(t_data *vars)
{
	// Destruo as sprites e a janela
	mlx_loop_end(vars->mlx);
	return (0);
}
void	display_moves(t_data *vars)
{
	char	*move_str;

	if (vars->player_info.move_count < 0)
		error_message(vars);
	move_str = ft_itoa(vars->player_info.move_count);
	if (!move_str)
		return ;
	draw_map(vars);
	mlx_string_put(vars->mlx, vars->win, 10, 20, 0xFFFFFF, "Movimentos:");
	ft_printf("Movimentos: %d\n", vars->player_info.move_count);
	mlx_string_put(vars->mlx, vars->win, 100, 20, 0xFFFFFF, move_str);
	free(move_str);
}

void    move_player(t_data *vars, int x_offset, int y_offset)
{
    int    new_x;
    int    new_y;

    new_x = vars->player_info.player_xstart + x_offset;
    new_y = vars->player_info.player_ystart + y_offset;
    if (vars->map.matrix[new_y][new_x] != '1')
    {
        if (vars->map.matrix[new_y][new_x] == 'C')
            vars->player_info.total_collectables--;
        else if (vars->map.matrix[new_y][new_x] == 'E')
        {
            if (vars->player_info.total_collectables == 0)
            {
                close_window(vars);
                return; // Retorne imediatamente
            }
            else
                return; // Não permitir movimento para a saída se houver coletáveis
        }
        vars->map.matrix[vars->player_info.player_ystart][vars->player_info.player_xstart] = '0';
        vars->map.matrix[new_y][new_x] = 'P';
        vars->player_info.player_xstart = new_x;
        vars->player_info.player_ystart = new_y;
        vars->player_info.move_count++;
        display_moves(vars);
    }
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	else if (keycode == LEFT_KEY)
		move_player(vars, -1, 0); // Mover para a esquerda
	else if (keycode == RIGHT_KEY)
		move_player(vars, 1, 0); // Mover para a direita
	else if (keycode == UP_KEY)
		move_player(vars, 0, -1); // Mover para cima
	else if (keycode == DOWN_KEY)
		move_player(vars, 0, 1); // Mover para baixo
	return (0);
}

void	create_window(t_data *vars)
{
	mlx_get_screen_size(vars->mlx, &vars->window_height, &vars->window_width);
	if (vars->window_height < vars->map.map_height
		|| vars->window_width < vars->map.map_width)
		error_message(vars);
	vars->win = mlx_new_window(vars->mlx, vars->map.map_width,
			vars->map.map_height, "So_long");
	vars->img = mlx_new_image(vars->mlx, vars->map.map_width,
			vars->map.map_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}
void	store_sprites(t_data *vars)
{
	vars->sprites.player = mlx_xpm_file_to_image(vars->mlx,
			"sprites/player.xpm", &vars->sprites.img_width,
			&vars->sprites.img_height);
	vars->sprites.collectables = mlx_xpm_file_to_image(vars->mlx,
			"sprites/collectable.xpm", &vars->sprites.img_width,
			&vars->sprites.img_height);
	vars->sprites.empty_space = mlx_xpm_file_to_image(vars->mlx,
			"sprites/empty_space.xpm", &vars->sprites.img_width,
			&vars->sprites.img_height);
	vars->sprites.escape = mlx_xpm_file_to_image(vars->mlx, "sprites/exit.xpm",
			&vars->sprites.img_width, &vars->sprites.img_height);
	vars->sprites.walls = mlx_xpm_file_to_image(vars->mlx, "sprites/wall.xpm",
			&vars->sprites.img_width, &vars->sprites.img_height);
	vars->sprites.escape_open = mlx_xpm_file_to_image(vars->mlx,
			"sprites/exit_open.xpm", &vars->sprites.img_width,
			&vars->sprites.img_height);
}

void	cleanup(t_data *vars)
{
	if (vars->map.matrix)
	{
		free_matrix(vars->map.matrix, vars->map.rows);
		vars->map.matrix = NULL;
	}
}

void	destroy_sprites(t_data *vars)
{
	mlx_destroy_image(vars->mlx, vars->sprites.player);
	mlx_destroy_image(vars->mlx, vars->sprites.collectables);
	mlx_destroy_image(vars->mlx, vars->sprites.empty_space);
	mlx_destroy_image(vars->mlx, vars->sprites.escape);
	mlx_destroy_image(vars->mlx, vars->sprites.walls);
	mlx_destroy_image(vars->mlx, vars->sprites.escape_open);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);

	mlx_loop_end(vars->mlx);
	// Liberar a matriz, se existir
	cleanup(vars);
	//free(vars->mlx);
	//exit(0);
}
