#include "so_long.h"

void	draw_img(t_data *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * 32, y * 32);
}
/*
int draw_map(t_data *vars, t_map *map, t_imgs *sprite) {
    int x;
    int y;

    y = 0;
    // Loop através das linhas da matriz até encontrar NULL
    while (map->matrix[y])
     {
       // printf("Processando linha %d: %s\n", y, map->matrix[y]);
        x = 0;
        // Loop através dos caracteres da linha até encontrar '\0'
        while (map->matrix[y][x]) {

            if(map->matrix[y][x] == '1')
                draw_img(vars, sprite->walls, x, y);
            x++;
        }
        y++;
    }
    return 0;
}
*/
void draw_map(t_data *vars, t_map *map, t_imgs *sprite)
{
    int x;
    int y;

    y = 0;
    while (y < map->rows)
    {
        x = 0;
        while (x < map->column)
        {
            if (map->matrix[y][x] == '1')
            {
                draw_img(vars, sprite->walls, x, y); // Desenhar parede
            }else if (map->matrix[y][x] == 'E')
            {
                draw_img(vars, sprite->empty_space, x, y); 
            }
            x++;
        }
        y++;
    }
}
