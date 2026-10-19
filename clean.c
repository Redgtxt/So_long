/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:28:47 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_image(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

static void	destroy_sprites(t_data *vars)
{
	destroy_image(vars->mlx, vars->sprites.player);
	destroy_image(vars->mlx, vars->sprites.collectables);
	destroy_image(vars->mlx, vars->sprites.empty_space);
	destroy_image(vars->mlx, vars->sprites.escape);
	destroy_image(vars->mlx, vars->sprites.walls);
	destroy_image(vars->mlx, vars->sprites.escape_open);
	ft_bzero(&vars->sprites, sizeof(t_imgs));
}

/* Releases whatever has been created so far, in reverse order. Safe to
   call at any point, which lets every error path share it. */
void	cleanup(t_data *vars)
{
	if (vars->mlx)
	{
		destroy_sprites(vars);
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		vars->mlx = NULL;
	}
	if (vars->map.matrix)
	{
		free_matrix(vars->map.matrix, vars->map.rows);
		vars->map.matrix = NULL;
	}
}

/* Only stops the loop; main does the cleanup once mlx_loop returns. */
int	close_window(t_data *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}
