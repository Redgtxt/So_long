/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_letters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei < hguerrei@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:29:20 by hguerrei          #+#    #+#             */
/*   Updated: 2024/10/15 10:52:48 by hguerrei         ###   ########.fr       */
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
	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == 'C')
				(*c_count)++;
			else if (vars->map.matrix[i][j] == 'P')
				(*p_count)++;
			else if (vars->map.matrix[i][j] == 'E')
				(*exit_count)++;
			else if (vars->map.matrix[i][j] != '0'
				&& vars->map.matrix[i][j] != '1')
				free_error(vars);
			j++;
		}
		i++;
	}
}

void	check_conditions(t_data *vars)
{
	int	c_count;
	int	p_count;
	int	exit_count;

	count_map_elements(vars, &c_count, &p_count, &exit_count);
	if (c_count <= 0 || p_count != 1 || exit_count != 1)
		error_message(vars);
}

void	find_player(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == 'P')
			{
				vars->player.p_x = j;
				vars->player.p_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
	error_message(vars);
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

void	check_path_player_to(t_data *vars)
{
	t_flood_fill	fill;
	char			**matrix_copy;

	matrix_copy = copy_matrix(vars);
	if (!matrix_copy)
		error_message(vars);
	fill.matrix_copy = matrix_copy;
	fill.rows = vars->map.rows;
	fill.columns = vars->map.column;
	fill.found_exit = 0;
	fill.collectibles = count_collectibles(vars);
	if (vars->player.p_x == -1 || vars->player.p_y == -1)
	{
		free_matrix(matrix_copy, vars->map.rows);
		error_message(vars);
	}
	flood_fill(&fill, vars->player.p_x, vars->player.p_y);
	if (fill.collectibles != 0 || fill.found_exit == 0)
	{
		free_matrix(matrix_copy, vars->map.rows);
		error_message(vars);
	}
	free_matrix(matrix_copy, vars->map.rows);
}
