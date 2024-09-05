#include "so_long.h"


int build_matrix(char *map, t_map *vars)
{
	int fd;
	int i;
	char *line;

	vars->matrix = (char **)malloc(vars->rows * sizeof(char *));
	if (!vars->matrix)
		return 0;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		// Armazena a linha na matriz
		vars->matrix[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return 1;
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


int	read_map(char *map,t_map *vars)
{
	int		fd;
	char	*line; 

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	vars->column = 0;
	while (line[vars->column] != '\0' && line[vars->column] != '\n')
		vars->column++;
	vars->rows = 0;
	while (line)
	{
		vars->rows++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	build_matrix(map,vars);
	check_walls(vars);
	check_rectangular(vars);
	return (0);
}


int	main(int argc, char *argv[])
{
	t_map vars;
	if (argc == 2)
		read_map(argv[1],&vars);


	
	for (int i = 0; i < vars.rows; i++)
	{
		ft_printf("%s", vars.matrix[i]);
		free(vars.matrix[i]);
	}
	free(vars.matrix);
	
}
