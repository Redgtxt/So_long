#include "so_long.h"

int build_matrix(char *map, t_map *vars)
{
	int fd;
	int i;
	char *line;

	// Alocação da matriz
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
		// ft_printf("%s",line); Desenha a linha
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	build_matrix(map,vars);

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
		free(vars.matrix[i]); // Libera a memória de cada linha
	}
	free(vars.matrix); // Libera a memória da matriz

}
