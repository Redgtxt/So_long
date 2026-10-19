/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:38:32 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_moves(t_data *vars)
{
	ft_printf("Movimentos: %d\n", vars->player.move_count);
	draw_counter(vars);
}

/* Moves the player one tile and redraws only the two tiles that changed. */
static void	step_to(t_data *vars, int x, int y)
{
	vars->map.matrix[vars->player.p_y][vars->player.p_x] = '0';
	vars->map.matrix[y][x] = 'P';
	draw_tile(vars, vars->player.p_x, vars->player.p_y);
	draw_tile(vars, x, y);
	vars->player.p_x = x;
	vars->player.p_y = y;
}

/* Walls and the closed exit block the move without counting it. Stepping
   onto the open exit counts as the last move and ends the game. */
void	move_player(t_data *vars, int x_offset, int y_offset)
{
	int		x;
	int		y;
	char	target;

	x = vars->player.p_x + x_offset;
	y = vars->player.p_y + y_offset;
	target = vars->map.matrix[y][x];
	if (target == '1' || (target == 'E' && vars->player.total_collectables))
		return ;
	vars->player.move_count++;
	if (target == 'E')
	{
		display_moves(vars);
		close_window(vars);
		return ;
	}
	if (target == 'C')
		vars->player.total_collectables--;
	step_to(vars, x, y);
	if (target == 'C' && vars->player.total_collectables == 0)
		draw_tile(vars, vars->map.exit_x, vars->map.exit_y);
	display_moves(vars);
}

int	key_hook(int keycode, t_data *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	else if (keycode == LEFT_KEY)
		move_player(vars, -1, 0);
	else if (keycode == RIGHT_KEY)
		move_player(vars, 1, 0);
	else if (keycode == UP_KEY)
		move_player(vars, 0, -1);
	else if (keycode == DOWN_KEY)
		move_player(vars, 0, 1);
	return (0);
}
