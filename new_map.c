#include "so_long.h"

int	build_matrix(char *map, t_map *vars)
{
	int		fd;
	int		i;
	char	*line;

	vars->matrix = (char **)malloc(vars->rows * sizeof(char *));
	if (!vars->matrix)
		error_message();
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
	check_walls(vars);
	check_rectangular(vars);
	check_letters(vars);
	return (1);
}


int	read_map(char *path, t_map *vars)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		error_message();
	}
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
	build_matrix(path, vars);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map	vars;

	if (argc == 2)
	{
		if (check_name(argv[1]))
			read_map(argv[1], &vars);
	}
	else
		error_message();

	for (int i = 0; i < vars.rows; i++)
	{
		ft_printf("%s", vars.matrix[i]);
		free(vars.matrix[i]);
	}
	free(vars.matrix);
}
