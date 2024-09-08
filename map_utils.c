#include "so_long.h"

int	ft_strlen_no_newline(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i] && string[i] != '\n')
		i++;
	return (i);
}

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
        if ((ft_strlen_no_newline(vars->matrix[i]) != vars->column)) // +1 para contar o '\n'
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





