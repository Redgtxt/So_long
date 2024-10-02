#include "so_long.h"

void free_error(t_data *vars)
{

	free_matrix(vars->map.matrix,vars->map.rows);
	error_message(vars);
}

void	count_map_elements(t_data *vars, int *c_count, int *p_count, int *exit_count)
{
	int i, j;

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
			else if (vars->map.matrix[i][j] != '0' && vars->map.matrix[i][j] != '1')
				free_error(vars);

			j++;
		}
		i++;
	}
}

void	check_conditions(t_data *vars)
{
	int c_count, p_count, exit_count;

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
				vars->player_info.player_xstart = j;
				vars->player_info.player_ystart = i;
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

void	flood_fill(char **matrix_copy, int x, int y, int rows, int columns,
		int *found_exit, int *collectibles)
{
	if (x < 0 || x >= columns || y < 0 || y >= rows || matrix_copy[y][x] == '1')
		return ;
	if (matrix_copy[y][x] == 'E')
	{
		*found_exit = 1;
		return ;
	}
	if (matrix_copy[y][x] == 'V')
		return ;
	if (matrix_copy[y][x] == 'C')
		(*collectibles)--;
	matrix_copy[y][x] = 'V';
	flood_fill(matrix_copy, x - 1, y, rows, columns, found_exit, collectibles); // Esquerda
	flood_fill(matrix_copy, x + 1, y, rows, columns, found_exit, collectibles); // Direita
	flood_fill(matrix_copy, x, y - 1, rows, columns, found_exit, collectibles); // Cima
	flood_fill(matrix_copy, x, y + 1, rows, columns, found_exit, collectibles); // Baixo
}

void	check_path_player_to(t_data *vars)
{
	int		found_exit;
	int		collectibles;
	char	**matrix_copy;

	found_exit = 0;
	matrix_copy = copy_matrix(vars);
	if (!matrix_copy)
		error_message(vars);
	collectibles = count_collectibles(vars);
	if (vars->player_info.player_xstart == -1
		|| vars->player_info.player_ystart == -1)
		error_message(vars);
	flood_fill(matrix_copy, vars->player_info.player_xstart,
		vars->player_info.player_ystart, vars->map.rows, vars->map.column,
		&found_exit, &collectibles);
	if (collectibles != 0 || found_exit == 0)
		error_message(vars);
	free_matrix(matrix_copy, vars->map.rows);
}

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
