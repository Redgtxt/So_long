#include "so_long.h"

void	draw_img(t_data *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * 32, y * 32);
}
void	draw_map(t_data *vars, t_map *map, t_imgs *sprite)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->column)
		{
			if (map->matrix[y][x] == '1')
				draw_img(vars, sprite->walls, x, y);
			else if (map->matrix[y][x] == '0')
				draw_img(vars, sprite->empty_space, x, y);
            else if (map->matrix[y][x] == 'P')
                draw_img(vars, sprite->player, x, y);
            else if (map->matrix[y][x] == 'C')
                draw_img(vars, sprite->collectables, x, y);
            else if(map->matrix[y][x] == 'E')
                draw_img(vars, sprite->escape, x, y);
			x++;
		}
		y++;
	}
}
