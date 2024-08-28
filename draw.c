#include "so_long.h"

void	draw_img(t_data *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * 32, y * 32);
}

int draw_map(t_data *vars,t_map *map,t_imgs *sprite)
{
    int x;
    int y;

    y = 0;
 while (map->matrix[y])
	{
    printf("Banana\n");
		x = 0;
		while (map->matrix[y][x])
		{
			draw_img(vars, sprite->walls, x, y);;
            x++;
        }
        y++;
    }
    return 0;
}
