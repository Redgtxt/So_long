#include "so_long.h"

/*
int	main(void)
{
	void	*img;
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1280, 720, "My Window");
	img = mlx_new_image(mlx, 1920, 1080);
	// Example usage: put the image to the window (replace with actual drawing code)
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	// Keep the window open
	mlx_loop(mlx);
}
*/

int	close_window(t_data *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0); // Encerrar o programa
	return (0);
}

int	key_hook(int keycode, t_data *vars)
{
	(void)vars;
	if (keycode == KEY_ESC)
	{
		ft_printf("ESC foi pressionado %d\n", keycode);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == LEFT_KEY)
	{
		ft_printf("KEY_LEFT foi pressionado %d\n", keycode);
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

void	create_window(t_data *vars,t_map *map)
{
	//vars->mlx = mlx_init();
    //mlx_get_screen_size(vars->mlx,&vars->window_width,&vars->window_height);
	 mlx_get_screen_size(vars->mlx, &vars->window_height, &vars->window_width);
    vars->win = mlx_new_window(vars->mlx, map->map_width, map->map_height, "So_long");
	vars->img = mlx_new_image(vars->mlx, map->map_width, map->map_height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}
void store_sprites(t_data *vars,t_imgs *sprite)
{
    sprite->player = mlx_xpm_file_to_image(vars->mlx, "sprites/skeleton.xpm", &sprite->img_width, &sprite->img_height);
    sprite->collectables = mlx_xpm_file_to_image(vars->mlx, "sprites/candle.xpm", &sprite->img_width, &sprite->img_height);
    sprite->empty_space = mlx_xpm_file_to_image(vars->mlx, "sprites/empty_space.xpm", &sprite->img_width, &sprite->img_height);
    sprite->walls = mlx_xpm_file_to_image(vars->mlx, "sprites/wall.xpm", &sprite->img_width, &sprite->img_height);
}
// int	main(void)
// {
// 	t_data	vars;
//     t_map map;

// 	// t_data img;
// 	// t_imgs sprite;
// 	// int img_width = 32;
// 	// int img_height = 32;
// 	// Carregando a sprite do arquivo XPM
// 	// sprite.player = mlx_xpm_file_to_image(vars.mlx, "sprites/skeleton.xpm",
// 			//&img_width, &img_height);
// 	// sprite.collectables = mlx_xpm_file_to_image(vars.mlx,
// 			//"sprites/candle.xpm", &img_width, &img_height);
// 	// Colocando a imagem da sprite na janela
// 	// mlx_put_image_to_window(vars.mlx, vars.win, sprite.player, 640, 360);
// 	// mlx_put_image_to_window(vars.mlx, vars.win, sprite.collectables, 20, 20);
// 	//
// 		// Adiciona o hook para fechar a janela quando o botão de fechar for clicado ou ESC pressionado
// 	// Evento de fechar a janela
// 	// mlx_key_hook(vars.win,key_hook,&vars);
// 	// Loop do MLX para manter a janela aberta
// 	create_window(&vars,&map);
// 	mlx_hook(vars.win, 17, 0, close_window, &vars);
// 	mlx_loop(vars.mlx);
// 	return (0);
// }

