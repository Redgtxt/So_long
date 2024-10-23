/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:28:47 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/23 11:58:26 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_error(t_data *vars)
{
	error_message(vars);
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
	cleanup(vars);
}

int	close_window(t_data *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}
