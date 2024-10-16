/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:01 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/15 10:44:45 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_img(t_data *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * SIZE_PIXEL, y
		* SIZE_PIXEL);
}

void	draw_tile(t_data *vars, int x, int y)
{
	if (vars->map.matrix[y][x] == '1')
		draw_img(vars, vars->sprites.walls, x, y);
	else if (vars->map.matrix[y][x] == '0')
		draw_img(vars, vars->sprites.empty_space, x, y);
	else if (vars->map.matrix[y][x] == 'P')
		draw_img(vars, vars->sprites.player, x, y);
	else if (vars->map.matrix[y][x] == 'C')
		draw_img(vars, vars->sprites.collectables, x, y);
	else if (vars->map.matrix[y][x] == 'E')
		draw_exit(vars, x, y);
}

void	draw_exit(t_data *vars, int x, int y)
{
	if (vars->player.total_collectables == 0)
		draw_img(vars, vars->sprites.escape_open, x, y);
	else
		draw_img(vars, vars->sprites.escape, x, y);
}

void	draw_map(t_data *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < vars->map.rows)
	{
		x = 0;
		while (x < vars->map.column)
		{
			draw_tile(vars, x, y);
			x++;
		}
		y++;
	}
}
