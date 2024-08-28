#include "so_long.h"

// Verifica se uma linha contém apenas o caractere '1'
void	parse_line(char *line, size_t length)
{
	size_t	i;

	i = 0;
	while (i < length - 1) // -1 para ignorar o '\n'
	{
		if (line[i] != '1')
			exit_program();
		i++;
	}
}

// Verifica se todas as colunas começam e terminam com '1'
void	validate_columns(char *line, size_t length)
{
	if (line[0] != '1' || line[length - 2] != '1') // -2 para ignorar o '\n'
		exit_program();
}

// Função para encontrar a posição do jogador 'P'
void	find_player(char **map, int map_size, size_t length, int *player_x,
		int *player_y)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (j < length - 1)
		{
			if (map[i][j] == 'P')
			{
				*player_x = i;
				*player_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
	exit_program(); // Se não encontrar o jogador, erro
}

// Função para realizar o flood fill
void	flood_fill(char **map, int x, int y, int map_size, size_t length)
{
	if (x < 0 || x >= map_size || y < 0 || y >= (int)length - 1)
		return ; // Fora dos limites
	if (map[x][y] == '1' || map[x][y] == 'V')
		return ; // Encontrou uma parede ou uma célula já visitada
	// Marca a célula como visitada
	map[x][y] = 'V';
	// Movimenta-se nas quatro direções
	flood_fill(map, x - 1, y, map_size, length); // UP
	flood_fill(map, x + 1, y, map_size, length); // DOWN
	flood_fill(map, x, y - 1, map_size, length); // LEFT
	flood_fill(map, x, y + 1, map_size, length); // RIGHT
}

// Verifica se todos os colecionáveis 'C' são acessíveis
void	check_collectables(char **map, int map_size, size_t length)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < map_size)
	{
		j = 0;
		while (j < length - 1) // -1 para ignorar o '\n'
		{
			if (map[i][j] == 'C')
				exit_program(); // Se encontrar um 'C' não visitado, erro
			j++;
		}
		i++;
	}
}

int	count_lines(int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	// Voltar para o início do arquivo
	lseek(fd, 0, SEEK_SET);
	return (lines);
}

void	read_map(int map_size, int fd, char *line, size_t length_first_line,
		t_map *vars)
{
	int	i;

	i = 1;
	while (i < map_size)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			exit_program(); // Exit if there's an error reading the line
		}
		// Verify that all lines have the same length
		if (ft_strlen(line) != length_first_line)
		{
			exit_program(); // Exit if line lengths don't match
		}
		// Verify that the first and last columns contain '1'
		validate_columns(line, length_first_line);
		// Store the line in the matrix
		vars->matrix[i] = line;
		i++;
	}
	// Set map dimensions
	vars->map_width = ft_strlen(vars->matrix[0]) * SIZE_PIXEL;
		// Assuming width is defined by line length
	vars->map_height = i * SIZE_PIXEL;
		// Assuming height is defined by the number of lines
																// Find the player's starting position
	// Remember to free `line` if it's dynamically allocated and no longer needed
}

void	pass_map(char *line, size_t length_first_line, t_map *map, int map_size,
		int fd)
{
	t_player_info	info;

	// Tenho de inicializar antes de usar se nao vai dar erro
	info.player_xstart = -1;
	info.player_ystart = -1;
	parse_line(line, length_first_line);
		// Verify the first line
	map->matrix[0] = line;
		// Store the first line in the matrix
	read_map(map_size, fd, line, length_first_line, map);
		// Read the rest of the map
	parse_line(map->matrix[map_size - 1], length_first_line);
		// Verify the last line
	printf("map[1] %s\n", map->matrix[1]);
	find_player(map->matrix, map_size, length_first_line, &info.player_xstart,
		&info.player_ystart);
	printf("Player position X: %d\n", info.player_xstart);
	printf("Player position Y: %d\n", info.player_ystart);
	// Perform flood fill from the player's starting position
	flood_fill(map->matrix, info.player_xstart, info.player_ystart, map_size,
		length_first_line);
	// Verify if all collectables are accessible
	check_collectables(map->matrix, map_size, length_first_line);
}

void	running_map(t_map *map, char *path)
{
	int		fd;
	size_t	length_first_line;
	char	*line;
	int		map_size;
	int		i;

	// Open the .ber file
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_program();
	// Count the number of lines in the file
	map_size = count_lines(fd);
	// Allocate memory for storing all lines of the map
	map->matrix = (char **)malloc(sizeof(char *) * map_size);
	if (!map->matrix)
		exit_program();
	// Read the first line of the map
	line = get_next_line(fd);
	if (line == NULL)
		exit_program();
	length_first_line = ft_strlen(line);
	pass_map(line, length_first_line, map, map_size, fd);
	// Memory cleanup and close the file
	i = 0;
	while (i < map_size)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	close(fd);
}

int	main(int argc, char *argv[])
{
	t_data			vars;
	t_map			map;
	t_player_info	info;
	t_imgs			sprite;

	if (argc == 2)
		check_name(argv[1]);
	else
	{
		exit_program();
	}
	init_variables(&vars, &info);
	running_map(&map, argv[1]);
	create_window(&vars, &map);
	draw_map(&vars, &map, &sprite);
	printf("ATE AQUI RODO\n");
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
