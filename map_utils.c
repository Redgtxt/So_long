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