#include "so_long.h"
/*
int main(void)
{
    void *img;
    void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1280, 720, "My Window");
    img = mlx_new_image(mlx, 1920, 1080);

    // Example usage: put the image to the window (replace with actual drawing code)
    mlx_put_image_to_window(mlx, win, img, 0, 0);

    // Keep the window open
    mlx_loop(mlx);
}
*/

int close_window(int keycode, t_data *vars)
{
    (void) keycode; // Evitar warnings de variável não usada
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0); // Encerrar o programa
    return (0);
}

int key_hook(int keycode, t_data *vars)
{
	(void) vars;
	if(keycode == KEY_ESC)
	{
		ft_printf("ESC foi pressionado %d\n", keycode);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0)
;	}else if(keycode == LEFT_KEY)
	{
		ft_printf("KEY_LEFT foi pressionado %d\n", keycode);
	}else if(keycode == RIGHT_KEY)
	{
		ft_printf("KEY_RIGHT foi pressionado %d\n", keycode);
	}else if(keycode == UP_KEY)
	{
		ft_printf("KEY_UP foi pressionado %d\n", keycode);
	}else if(keycode == DOWN_KEY)
	{
		ft_printf("KEY_DOWN foi pressionado %d\n", keycode);
	}
	return 0;
}


int	main(void)
{

    t_data img;
    t_data vars;
    t_data sprite_img;
    int img_width = 32;
    int img_height = 32;

   vars.mlx = mlx_init();

    vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");


    // Criando a imagem da janela principal
    img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

    // Carregando a sprite do arquivo XPM
    sprite_img.img = mlx_xpm_file_to_image(vars.mlx, "sprites/skeleton.xpm", &img_width, &img_height);


    // Colocando a imagem da sprite na janela
    mlx_put_image_to_window(vars.mlx, vars.win, sprite_img.img, 640, 360);

    // Adiciona o hook para fechar a janela quando o botão de fechar for clicado ou ESC pressionado
    mlx_hook(vars.win, 17, 0, close_window, &vars); // Evento de fechar a janela
	mlx_key_hook(vars.win,key_hook,&vars);

    // Loop do MLX para manter a janela aberta
    mlx_loop(vars.mlx);

    return (0);
}


