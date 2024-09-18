/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:20:45 by hguerrei          #+#    #+#             */
/*   Updated: 2024/09/18 13:48:54 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

void	game_hooks(t_data *vars)
{
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_key_hook(vars->win, key_hook, vars);
}
int	main(int argc, char *argv[])
{
	t_data	vars;

	if (argc == 2)
	{
		if (check_name(argv[1]))
			read_map(argv[1], &vars);
	}
	else
        error_message();
	// Criando a janela
	vars.mlx = mlx_init();
	create_window(&vars);
	store_sprites(&vars);
	draw_map(&vars);
	game_hooks(&vars);
	mlx_loop(vars.mlx);
	free(vars.map.matrix);
}
