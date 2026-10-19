/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 15:55:14 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_window(t_data *vars)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(vars->mlx, &screen_width, &screen_height);
	if (screen_width < vars->map.map_width
		|| screen_height < vars->map.map_height)
		error_message(vars, "the map is larger than the screen");
	vars->win = mlx_new_window(vars->mlx, vars->map.map_width,
			vars->map.map_height, "So_long");
	if (!vars->win)
		error_message(vars, "cannot open a window");
}

static void	*load_sprite(t_data *vars, char *path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(vars->mlx, path, &width, &height);
	if (!img)
		error_message(vars, "cannot load the sprites from sprites/");
	return (img);
}

/* Paths are relative, so the game must be started from the repository. */
void	store_sprites(t_data *vars)
{
	vars->sprites.player = load_sprite(vars, "sprites/player.xpm");
	vars->sprites.collectables = load_sprite(vars, "sprites/collectable.xpm");
	vars->sprites.empty_space = load_sprite(vars, "sprites/empty_space.xpm");
	vars->sprites.escape = load_sprite(vars, "sprites/exit.xpm");
	vars->sprites.walls = load_sprite(vars, "sprites/wall.xpm");
	vars->sprites.escape_open = load_sprite(vars, "sprites/exit_open.xpm");
}
