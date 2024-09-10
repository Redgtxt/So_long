#include "so_long.h"

void game_hooks(t_data *vars)
{
    mlx_hook(vars->win, 17, 0, close_window, vars);
    mlx_key_hook(vars->win, key_hook, vars);
}
/*
void init_game(t_data *vars, t_map *map, t_imgs *sprite)
{
    vars->mlx = mlx_init();
    mlx_get_screen_size(vars->mlx, &vars->window_height, &vars->window_width);
    vars->win = mlx_new_window(vars->mlx, map->map_width, map->map_height, "So_long");
    store_sprites(vars, sprite);
    draw_map(vars, map, sprite);
}
*/
int	main(int argc, char *argv[])
{
	t_data			vars;
    t_map			map;
    t_imgs          sprite;

	if (argc == 2)
	{
		if (check_name(argv[1]))
			read_map(argv[1], &map);
	}
	else
		error_message();
    
    //Criando a janela
    vars.mlx = mlx_init();
    create_window(&vars, &map);
    store_sprites(&vars, &sprite);
    draw_map(&vars, &map, &sprite);
    game_hooks(&vars);
    mlx_loop(vars.mlx);
	for (int i = 0; i < map.rows; i++)
	{
		ft_printf("%s", map.matrix[i]);
		free(map.matrix[i]);
	}
	free(map.matrix);
}