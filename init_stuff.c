/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:11 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_variables(t_data *vars)
{
	vars->player.move_count = 0;
	vars->player.total_collectables = count_collectibles(vars);
}

void	check_letters(t_data *vars)
{
	check_conditions(vars);
	init_variables(vars);
	find_tile(vars, 'P', &vars->player.p_x, &vars->player.p_y);
	find_tile(vars, 'E', &vars->map.exit_x, &vars->map.exit_y);
	check_path_player_to(vars);
}

/* Marks a cell as visited and queues it for expansion. The exit is
   recorded as reached but never expanded: in the game the player cannot
   walk through it, so nothing behind it counts as reachable. */
static void	push_cell(t_flood_fill *fill, int x, int y)
{
	char	*cell;

	if (x < 0 || x >= fill->columns || y < 0 || y >= fill->rows)
		return ;
	cell = &fill->matrix_copy[y][x];
	if (*cell == '1' || *cell == 'V')
		return ;
	if (*cell == 'E')
		fill->found_exit = 1;
	if (*cell == 'C')
		fill->collectibles--;
	if (*cell != 'E')
		fill->stack[fill->top++] = y * fill->columns + x;
	*cell = 'V';
}

/* Iterative, with an explicit stack instead of recursion, so the depth no
   longer grows with the size of the map. Each cell is pushed at most once,
   so the stack never needs more than rows * columns entries. */
void	flood_fill(t_flood_fill *fill, int x, int y)
{
	int	pos;

	push_cell(fill, x, y);
	while (fill->top > 0)
	{
		pos = fill->stack[--fill->top];
		x = pos % fill->columns;
		y = pos / fill->columns;
		push_cell(fill, x - 1, y);
		push_cell(fill, x + 1, y);
		push_cell(fill, x, y - 1);
		push_cell(fill, x, y + 1);
	}
}
