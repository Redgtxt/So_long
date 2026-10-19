/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_letters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:20 by hguerrei          #+#    #+#             */
/*   Updated: 2026/10/19 15:55:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_elements(t_data *vars, int *c_count, int *p_count,
		int *exit_count)
{
	int	i;
	int	j;

	*c_count = 0;
	*p_count = 0;
	*exit_count = 0;
	i = -1;
	while (++i < vars->map.rows)
	{
		j = -1;
		while (++j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == 'C')
				(*c_count)++;
			else if (vars->map.matrix[i][j] == 'P')
				(*p_count)++;
			else if (vars->map.matrix[i][j] == 'E')
				(*exit_count)++;
			else if (vars->map.matrix[i][j] != '0'
				&& vars->map.matrix[i][j] != '1')
				error_message(vars, "the map may only contain 0, 1, C, E, P");
		}
	}
}

void	check_conditions(t_data *vars)
{
	int	c_count;
	int	p_count;
	int	exit_count;

	count_map_elements(vars, &c_count, &p_count, &exit_count);
	if (c_count <= 0 || p_count != 1 || exit_count != 1)
		error_message(vars, "the map needs one P, one E and at least one C");
}

void	find_tile(t_data *vars, char tile, int *x, int *y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < vars->map.rows)
	{
		j = -1;
		while (++j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == tile)
			{
				*x = j;
				*y = i;
				return ;
			}
		}
	}
}

int	count_collectibles(t_data *vars)
{
	int	collectibles;
	int	i;
	int	j;

	collectibles = 0;
	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == 'C')
				collectibles++;
			j++;
		}
		i++;
	}
	return (collectibles);
}

/* Runs the flood fill on a copy of the map, with an explicit stack big
   enough for every cell, and frees both on every path out. */
void	check_path_player_to(t_data *vars)
{
	t_flood_fill	fill;
	char			*reason;

	reason = NULL;
	fill.rows = vars->map.rows;
	fill.columns = vars->map.column;
	fill.found_exit = 0;
	fill.collectibles = count_collectibles(vars);
	fill.top = 0;
	fill.matrix_copy = copy_matrix(vars);
	fill.stack = malloc(sizeof(int) * fill.rows * fill.columns);
	if (!fill.matrix_copy || !fill.stack)
		reason = "out of memory";
	else
	{
		flood_fill(&fill, vars->player.p_x, vars->player.p_y);
		if (fill.collectibles != 0 || !fill.found_exit)
			reason = "not every collectible and the exit can be reached";
	}
	free(fill.stack);
	if (fill.matrix_copy)
		free_matrix(fill.matrix_copy, fill.rows);
	if (reason)
		error_message(vars, reason);
}
