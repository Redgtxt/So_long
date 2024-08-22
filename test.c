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


int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_data	sprite_img;
	int		img_width = 32;
	int		img_height = 32;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");

	// Criando a imagem da janela principal
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);

	// Carregando a sprite do arquivo XPM
	sprite_img.img = mlx_xpm_file_to_image(mlx, "sprites/Owlet_Monster.xpm", &img_width, &img_height);

	if (!sprite_img.img)
	{
		// Caso a imagem não tenha sido carregada corretamente
		return (1);
	}

	// Colocando a imagem da sprite na janela
	mlx_put_image_to_window(mlx, mlx_win, sprite_img.img, 640, 360);

	// Loop do MLX para manter a janela aberta
	mlx_loop(mlx);
}

