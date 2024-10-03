#include "so_long.h"

int	is_valid_position(t_data *vars, int x, int y)
{
	if (x < 0 || x >= vars->map.column || y < 0 || y >= vars->map.rows)
		return (0);
	if (vars->map.matrix[y][x] == '1' || vars->map.matrix[y][x] == 'V')
		return (0);
	return (1);
}
/*
void	handle_element(t_data *vars, int x, int y)
{
	if (vars->map.matrix[y][x] == 'C')
		vars->collectibles--;   // Acessa o campo `collectibles` diretamente
	else if (vars->map.matrix[y][x] == 'E')
		vars->found_exit = 1;   // Acessa o campo `found_exit` diretamente
	vars->map.matrix[y][x] = 'V'; // Marca a célula como visitada
}
*/
void	flood_fill_core(t_data *vars, int x, int y)
{
	if (!is_valid_position(vars, x, y))
		return;
	
	handle_element(vars, x, y);

	// Recursão para todas as direções
	flood_fill_core(vars, x - 1, y); // Esquerda
	flood_fill_core(vars, x + 1, y); // Direita
	flood_fill_core(vars, x, y - 1); // Cima
	flood_fill_core(vars, x, y + 1); // Baixo
}

