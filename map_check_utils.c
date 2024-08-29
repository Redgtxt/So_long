#include "so_long.h"
void exit_program(void)
{
    ft_printf("Mensagem de erro customizada\n");
    exit(EXIT_FAILURE);
}

int check_name (char *path)
{
    int i;

    i = 0;
    while (path[i] && path[i] != '.')
        i++;
    if(path[i] == '\0' || ft_strncmp(path + i,".ber",4) != 0)
    {
        exit_program();
    }
    return 1;
}

void init_variables(t_data *vars) {
    // Inicializar t_data vars
    vars->mlx = mlx_init();

    vars->win = NULL;
    vars->img = NULL;
    vars->addr = NULL;
    vars->bits_per_pixel = 0;
    vars->line_length = 0;
    vars->endian = 0;
}

void	flood_fill(char **map, int x, int y, int map_size, size_t length)
{
    if (x < 0 || x >= map_size || y < 0 || y >= (int)length - 1)
        return; // Fora dos limites

    if (map[x][y] == '1' || map[x][y] == 'V')
        return; // Encontrou uma parede ou uma célula já visitada

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
