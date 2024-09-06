#include "so_long.h"

void check_walls(t_map *vars)
{
    int i;

	i = 0;
    while (i < vars->column )
    {
        if (vars->matrix[0][i] != '1' || vars->matrix[vars->rows - 1][i] != '1')
        {
            error_message();
        }
		i++;
    }

	i = 0;
    while ( i < vars->rows)
    {
        if (vars->matrix[i][0] != '1' || vars->matrix[i][vars->column - 1] != '1')
        {
            error_message();
        }
		i++;
    }
}

void error_message(void)
{
	ft_printf("ERROR\n");
	exit(1);
}

void check_rectangular(t_map *vars)
{
    int i;

	i = 0;
    while ( i < vars->rows)
    {
        if ((int)ft_strlen(vars->matrix[i]) != vars->column + 1) // +1 para contar o '\n'
        {
            error_message();
        }
	i++;
    }
}
int check_name (char *path)
{
    int i;

    i = 0;
    while (path[i] && path[i] != '.')
        i++;
    if(path[i] == '\0' || ft_strncmp(path + i,".ber",4) != 0)
    {
        error_message();
    }
    return 1;
}

void find_player(t_map *vars, int *player_x, int *player_y)
{
    int i;
    int j;

    i = 0;
    while (i < vars->rows)  // Alterado de vars->column para vars->rows
    {
        j = 0;
        while (j < vars->column)  // Alterado de vars->rows para vars->column
        {
            if (vars->matrix[i][j] == 'P')
            {
                *player_x = i;
                *player_y = j;
                printf("Jogador encontrado na posição X: %d, Y: %d\n", *player_x, *player_y);
                return;
            }
            j++;
        }
        i++;
    }
    error_message();
}


void check_letters(t_map *vars)
{
	t_player_info info;
	info.player_xstart = -1;
	info.player_ystart = -1;
	find_player(vars,&info.player_xstart,&info.player_ystart);
}
