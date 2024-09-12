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
	vars->map_width = vars->column * 32;
	vars->map_height = vars->rows * 32;
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

char	**copy_matrix(t_map *vars)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (vars->rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < vars->rows)
	{
		copy[i] = ft_strdup(vars->matrix[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
void	free_matrix(char **matrix, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
