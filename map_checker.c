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
void find_player(char **map, int map_size, size_t length, int *player_x, int *player_y) {
    int i;
    size_t j;

    i = 0;
    while (i < map_size) {
        j = 0;
        while (j < length - 1) {
            if (map[i][j] == 'P') {
                *player_x = i;
                *player_y = j;
                printf("Jogador encontrado na posição X: %d, Y: %d\n", *player_x, *player_y);
                return;
            }
            j++;
        }
        i++;
    }
    exit_program(); // Se não encontrar o jogador, erro
}


int count_lines(int fd) {
    int lines;
    char *line;

    lines = 0;
    line = get_next_line(fd);
    while (line) {
        lines++;
        free(line);
        line = get_next_line(fd);
    }
    // Voltar para o início do arquivo
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek error");
        exit_program();
    }
    return lines;
}
void read_map(int map_size, int fd, char *line, size_t length_first_line, t_map *vars) {
    int i;

    i = 1;
    while (i < map_size) {
        line = get_next_line(fd);
        if (line == NULL) {
            printf("Erro ao ler linha %d\n", i);
            exit_program(); // Exit if there's an error reading the line
        }
        printf("Linha %d lida: %s\n", i, line);  // Adicionado para depuração
        // Verify that all lines have the same length
        if (ft_strlen(line) != length_first_line) {
            printf("Comprimento da linha %d não corresponde ao esperado.\n", i);
            exit_program(); // Exit if line lengths don't match
        }
        // Verify that the first and last columns contain '1'
        validate_columns(line, length_first_line);
        // Store the line in the matrix
        vars->matrix[i] = line;
        i++;
    }
    vars->matrix[i] = NULL; // Adiciona NULL para finalizar a matriz
    printf("Todas as linhas foram lidas e armazenadas.\n");



 	// Set map dimensions
    vars->map_width = ft_strlen(vars->matrix[0]) * SIZE_PIXEL;
    vars->map_height = i * SIZE_PIXEL;

}

void pass_map(char *line, size_t length_first_line, t_map *map, int map_size, int fd) {
    t_player_info info;

    info.player_xstart = -1; // Inicializar antes de usar
    info.player_ystart = -1; // Inicializar antes de usar


    map->matrix[0] = line;
    parse_line(line, length_first_line); // Verificar a primeira linha

    // Ler o resto do mapa
    read_map(map_size, fd, line, length_first_line, map);

    parse_line(map->matrix[map_size - 1], length_first_line); // Verificar a última linha

    printf("map[0]: %s\n", map->matrix[0]); // Imprimir a primeira linha para depuração
    printf("map[1]: %s\n", map->matrix[1]); // Imprimir a segunda linha para depuração

    find_player(map->matrix, map_size, length_first_line, &info.player_xstart, &info.player_ystart);

    // Realizar flood fill a partir da posição inicial do jogador
    flood_fill(map->matrix, info.player_xstart, info.player_ystart, map_size, length_first_line);

    // Verificar se todos os colecionáveis são acessíveis
    check_collectables(map->matrix, map_size, length_first_line);
}


void	running_map(t_map *map, char *path)
{
	int		fd;
	size_t	length_first_line;
	char	*line;
	int		map_size;
	int		i;

	// Abrir o arquivo .ber
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_program();
	// Contar o número de linhas no arquivo
	map_size = count_lines(fd);
	// Alocar memória para armazenar todas as linhas do mapa
	map->matrix = (char **)malloc(sizeof(char *) * (map_size + 1));
	if (!map->matrix)
		exit_program(); // Verificar se a alocação de memória foi bem-sucedida
	// Ler a primeira linha do mapa
	line = get_next_line(fd);
	if (line == NULL)
		exit_program(); // Verificar se a leitura foi bem-sucedida
	length_first_line = ft_strlen(line);

	pass_map(line, length_first_line, map, map_size, fd);

	i = 0;
	while (i < map_size)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	close(fd);
}

int	main(int argc, char *argv[]) {
    t_data			vars;
    t_map			map;
    t_imgs			sprite;

    if (argc == 2) {
        check_name(argv[1]);
    } else {
        exit_program();
    }

    // Inicializar variáveis e MLX
    init_variables(&vars);
    running_map(&map, argv[1]);
    create_window(&vars, &map);

    // Carregar sprites
    store_sprites(&vars, &sprite);

    // Desenhar mapa
    draw_map(&vars, &map, &sprite);
    printf("ATE AQUI RODO\n");

    // Configurar eventos MLX
    mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);
    return 0;
}

