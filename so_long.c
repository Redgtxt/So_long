/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:37:25 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/15 10:57:31 by hguerrei         ###   ########.fr       */
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

	vars.map.matrix = NULL;
	if (argc == 2)
	{
		if (check_name(argv[1], &vars))
			read_map(argv[1], &vars);
	}
	else
		error_message(&vars);
	vars.mlx = mlx_init();
	create_window(&vars);
	store_sprites(&vars);
	draw_map(&vars);
	game_hooks(&vars);
	mlx_loop(vars.mlx);
	destroy_sprites(&vars);
	free(vars.mlx);
	return (0);
}
