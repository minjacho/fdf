#include "fdf.h"

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_point p[20][20];
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int i = 0; i<600; i+=30)
	{
		for (int j = 0; j < 600; j+=30)
		{
			p[i / 30][j / 30].x = i;
			p[i / 30][j / 30].y = j;
			p[i / 30][j / 30].z = 0;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			rotate(&p[i][j]);
			project(&p[i][j], M_PI / 6);
			p[i][j].x += 600;
			p[i][j].y += 200;
		}
	}
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			put_line_on_window(&img, p[i][j], p[i + 1][j]);
			put_line_on_window(&img, p[i][j], p[i][j + 1]);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
