#include "so_long.h"

void game_hooks(t_data *vars)
{
    mlx_hook(vars->win, 17, 0, close_window, vars);
    mlx_key_hook(vars->win, key_hook, vars);
}
int	main(int argc, char *argv[])
{
	t_data			vars;

	 vars.map.matrix = NULL;

	if (argc == 2)
	{
		if (check_name(argv[1]))
			read_map(argv[1], &vars);
	}
	else
		error_message();
    //Criando a janela
    vars.mlx = mlx_init();
    create_window(&vars);
    store_sprites(&vars);
    draw_map(&vars);
    game_hooks(&vars);
    mlx_loop(vars.mlx);
}
