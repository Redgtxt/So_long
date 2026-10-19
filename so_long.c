/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:37:25 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* 17 is DestroyNotify, which MiniLibX also sends for the close button.
   The expose hook repaints the window whenever the system asks for it,
   since moves only redraw the tiles that changed. */
static void	game_hooks(t_data *vars)
{
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_key_hook(vars->win, key_hook, vars);
	mlx_expose_hook(vars->win, draw_map, vars);
}

int	main(int argc, char *argv[])
{
	t_data	vars;

	ft_bzero(&vars, sizeof(t_data));
	if (argc != 2)
		error_message(&vars, "usage: ./so_long <map.ber>");
	check_name(argv[1], &vars);
	read_map(argv[1], &vars);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		error_message(&vars, "cannot connect to the X server");
	create_window(&vars);
	store_sprites(&vars);
	draw_map(&vars);
	game_hooks(&vars);
	mlx_loop(vars.mlx);
	cleanup(&vars);
	return (0);
}
