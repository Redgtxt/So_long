#include "so_long.h"

void	find_player(t_map *vars, int *player_x, int *player_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->rows)
	{
		j = 0;
		while (j < vars->column)
		{
			if (vars->matrix[i][j] == 'P')
			{
				*player_x = j ;
				*player_y = i;
				 printf("Jogador encontrado na posição X: %d, Y: %d\n",
					*player_x, *player_y);
				return ;
			}
			j++;
		}
		i++;
	}
	error_message();
}

int count_collectibles(t_map *vars)
{
    int collectibles = 0;
    int i = 0;
    int j;

    while (i < vars->rows)
    {
        j = 0;
        while (j < vars->column)
        {
            if (vars->matrix[i][j] == 'C')
                collectibles++;
            j++;
        }
        i++;
    }
    return collectibles;
}

void	check_conditions(t_map *vars)
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
	while (i < vars->rows)
	{
		j = 0;
		while (j < vars->column)
		{
			if (vars->matrix[i][j] == 'C')
				c_count++;
			if (vars->matrix[i][j] == 'P')
				p_count++;
			if (vars->matrix[i][j] == 'E')
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




void check_path_player_to(t_map *vars, t_player_info *info)
{
    int found_exit = 0;
    int collectibles;
    char **matrix_copy;

    matrix_copy = copy_matrix(vars);
    if (!matrix_copy)
        error_message();

    collectibles = count_collectibles(vars);

    if (info->player_xstart == -1 || info->player_ystart == -1)
        error_message();

    flood_fill(matrix_copy, info->player_xstart, info->player_ystart, vars->rows,vars->column,&found_exit, &collectibles);

    if (collectibles != 0 || found_exit == 0)
        error_message();

    free_matrix(matrix_copy, vars->rows);
}



void	check_letters(t_map *vars)
{
	t_player_info	info;

	info.player_xstart = -1;
	info.player_ystart = -1;
	find_player(vars, &info.player_xstart, &info.player_ystart);
	check_conditions(vars);
	check_path_player_to(vars, &info);
}
