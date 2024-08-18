#include "so_long.h"

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