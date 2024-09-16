#include "so_long.h"

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
				 printf("Jogador encontrado na posição X: %d, Y: %d\n",
					vars->player_info.player_xstart,vars->player_info.player_ystart);
				return ;
			}
			j++;
		}
		i++;
	}
	error_message();
}

int count_collectibles(t_data *vars)
{
    int collectibles = 0;
    int i = 0;
    int j;

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
    return collectibles;
}

void	check_conditions(t_data *vars)
{
	int	i;
	int	j;
	int	c_count;
	int	p_count;
	int	exit_count;

	exit_count = 0;
	p_count = 0;
	c_count = 0;
	i = 0;
	while (i < vars->map.rows)
	{
		j = 0;
		while (j < vars->map.column)
		{
			if (vars->map.matrix[i][j] == 'C')
				c_count++;
			if (vars->map.matrix[i][j] == 'P')
				p_count++;
			if (vars->map.matrix[i][j] == 'E')
				exit_count++;
			j++;
		}
		i++;
	}
	if (c_count <= 0 || p_count != 1 || exit_count != 1)
		error_message();
}

void flood_fill(char **matrix_copy, int x, int y, int rows, int columns, int *found_exit, int *collectibles)
{

    if (x < 0 || x >= columns || y < 0 || y >= rows || matrix_copy[y][x] == '1')
        return;


    if (matrix_copy[y][x] == 'E')
    {
        *found_exit = 1;
        return;
    }


    if (matrix_copy[y][x] == 'V')
        return;

    if (matrix_copy[y][x] == 'C')
        (*collectibles)--;

    matrix_copy[y][x] = 'V';

    // Chamadas recursivas para explorar as quatro direções (esquerda, direita, cima, baixo)
    flood_fill(matrix_copy, x - 1, y, rows, columns, found_exit, collectibles);  // Esquerda
    flood_fill(matrix_copy, x + 1, y, rows, columns, found_exit, collectibles);  // Direita
    flood_fill(matrix_copy, x, y - 1, rows, columns, found_exit, collectibles);  // Cima
    flood_fill(matrix_copy, x, y + 1, rows, columns, found_exit, collectibles);  // Baixo
}




void check_path_player_to(t_data *vars)
{
    int found_exit = 0;
    int collectibles;
    char **matrix_copy;

    matrix_copy = copy_matrix(vars);
    if (!matrix_copy)
        error_message();

    collectibles = count_collectibles(vars);

    if (vars->player_info.player_xstart == -1 || vars->player_info.player_ystart == -1)
        error_message();

    flood_fill(matrix_copy, vars->player_info.player_xstart, vars->player_info.player_ystart, vars->map.rows,vars->map.column,&found_exit, &collectibles);

    if (collectibles != 0 || found_exit == 0)
        error_message();

    free_matrix(matrix_copy, vars->map.rows);
}


void init_variables(t_data *vars)
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
