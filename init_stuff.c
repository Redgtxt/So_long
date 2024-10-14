/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:11 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/14 14:29:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_variables(t_data *vars)
{
	vars->player_info.player_xstart = -1;
	vars->player_info.player_ystart = -1;
	vars->player_info.total_collectables = -1;
	vars->player_info.move_count = 0;
	vars->player_info.total_collectables = count_collectibles(vars);
}

void	check_letters(t_data *vars)
{
	init_variables(vars);
	find_player(vars);
	check_conditions(vars);
	check_path_player_to(vars);
}
void	flood_fill(t_flood_fill *fill, int x, int y)
{
	if (x < 0 || x >= fill->columns || y < 0 || y >= fill->rows
		|| fill->matrix_copy[y][x] == '1')
		return ;
	if (fill->matrix_copy[y][x] == 'E')
	{
		fill->found_exit = 1;
		return ;
	}
	if (fill->matrix_copy[y][x] == 'V')
		return ;
	if (fill->matrix_copy[y][x] == 'C')
		fill->collectibles--;
	fill->matrix_copy[y][x] = 'V';
	flood_fill(fill, x - 1, y);
	flood_fill(fill, x + 1, y);
	flood_fill(fill, x, y - 1);
	flood_fill(fill, x, y + 1);
}
