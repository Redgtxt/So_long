#include "so_long.h"

int	close_window(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0); // Encerrar o programa
	return (0);
}


void move_player(t_data *vars)
{
	printf("X:Player:%d\n",vars->player_info.player_xstart);
	printf("Y:Player:%d\n",vars->player_info.player_ystart);
}


int	key_hook(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
	{

		ft_printf("ESC foi pressionado %d\n", keycode);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == LEFT_KEY)
	{
		ft_printf("KEY_LEFT foi pressionado %d\n", keycode);
		move_player(vars);
	}
	else if (keycode == RIGHT_KEY)
	{
		ft_printf("KEY_RIGHT foi pressionado %d\n", keycode);
	}
	else if (keycode == UP_KEY)
	{
		ft_printf("KEY_UP foi pressionado %d\n", keycode);
	}
	else if (keycode == DOWN_KEY)
	{
		ft_printf("KEY_DOWN foi pressionado %d\n", keycode);
	}
	return (0);
}

void	create_window(t_data *vars)
{
	//vars->mlx = mlx_init();
    //mlx_get_screen_size(vars->mlx,&vars->window_width,&vars->window_height);
	 mlx_get_screen_size(vars->mlx, &vars->window_height, &vars->window_width);
    vars->win = mlx_new_window(vars->mlx, vars->map.map_width, vars->map.map_height, "So_long");
	vars->img = mlx_new_image(vars->mlx, vars->map.map_width, vars->map.map_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}
void store_sprites(t_data *vars)
{
    vars->sprites.player = mlx_xpm_file_to_image(vars->mlx, "sprites/player.xpm", &vars->sprites.img_width, &vars->sprites.img_height);
    vars->sprites.collectables = mlx_xpm_file_to_image(vars->mlx, "sprites/collectable.xpm", &vars->sprites.img_width, &vars->sprites.img_height);
    vars->sprites.empty_space = mlx_xpm_file_to_image(vars->mlx, "sprites/empty_space.xpm", &vars->sprites.img_width, &vars->sprites.img_height);
    vars->sprites.escape = mlx_xpm_file_to_image(vars->mlx, "sprites/exit.xpm", &vars->sprites.img_width, &vars->sprites.img_height);
    vars->sprites.walls = mlx_xpm_file_to_image(vars->mlx, "sprites/wall.xpm", &vars->sprites.img_width, &vars->sprites.img_height);
}


