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
		char **matrix)
{
	int	i;

	i = 1;
	while (i < map_size)
	{
		line = get_next_line(fd);
		if (line == NULL)
			exit_program();
		// Verifica se todas as linhas têm o mesmo comprimento
		if (ft_strlen(line) != length_first_line)
			exit_program();
		// Verifica se a primeira e a última coluna contêm '1'
		validate_columns(line, length_first_line);
		matrix[i] = line;
		i++;
	}
}

void	pass_map(char *line, size_t length_first_line, t_map map, int map_size,
		int fd)
{
	t_player_info	info;

	parse_line(line, length_first_line); // Verifica a primeira linha
	map.matrix[0] = line;
	read_map(map_size, fd, line, length_first_line, map.matrix);
	// Verifica a última linha
	parse_line(map.matrix[map_size - 1], length_first_line);
	// Encontra a posição inicial do jogador
	find_player(map.matrix, map_size, length_first_line, &info.player_xstart,
		&info.player_ystart);
	printf("Posicao do player X: %d\n", info.player_xstart);
	printf("Posicao do player Y: %d\n", info.player_ystart);
	// Executa o flood fill a partir da posição do jogador
	flood_fill(map.matrix, info.player_xstart, info.player_ystart, map_size,
		length_first_line);
	// Verifica se todos os colecionáveis são acessíveis
	check_collectables(map.matrix, map_size, length_first_line);
}
/*
int	main(void)
{
	int		fd;
	size_t	length_first_line;
	char	*line;
	int		map_size;
	t_map	map;
	int		i;

	// Abre o arquivo .ber
	fd = open("map.ber", O_RDONLY);
	if (fd < 0)
		exit_program();
	// Conta o número de linhas no arquivo
	map_size = count_lines(fd);
	// Aloca memória para armazenar todas as linhas do mapa
	map.matrix = (char **)malloc(sizeof(char *) * map_size);
	if (!map.matrix)
		exit_program();
	// Lê a primeira linha do mapa
	line = get_next_line(fd);
	if (line == NULL)
		exit_program();
	length_first_line = ft_strlen(line);
	pass_map(line, length_first_line, map, map_size, fd);
	// Libera a memória e fecha o arquivo
	i = 0;
	while (i < map_size)
	{
		free(map.matrix[i]);
		i++;
	}
	free(map.matrix);
	close(fd);
	return (0);
}
*/
