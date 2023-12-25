/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:47:59 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/25 16:20:17 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_leak(void)
{
	system("leaks a.out");
}

void	mlx_main(t_info *info)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, MLX_SIZE_X, MLX_SIZE_Y, "fdf");
	img.img = mlx_new_image(mlx, MLX_SIZE_X, MLX_SIZE_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	for (int i = 0; i < info->y_size; i++)
	{
		for (int j = 0; j < info->x_size; j++)
		{
			rotate(&info->points[i][j]);
			project(&info->points[i][j], M_PI / 6);
			info->points[i][j].x += 400;
			info->points[i][j].y += 100;
		}
	}
	for (int i = 0; i < info->y_size; i++)
	{
		for (int j = 0; j < info->x_size; j++)
		{
			if (i != info->y_size - 1)
				put_line_on_window(&img, info->points[i][j], info->points[i + 1][j], info);
			if (j != info->x_size - 1)
				put_line_on_window(&img, info->points[i][j], info->points[i][j + 1], info);
			if (i != 0)
				put_line_on_window(&img, info->points[i][j], info->points[i - 1][j], info);
			if (j != 0)
				put_line_on_window(&img, info->points[i][j], info->points[i][j - 1], info);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}


int main(int argc, char *argv[])
{
	int		fd;
	t_info	info;

	atexit(check_leak);
	if (argc != 2)
		exit(EXIT_SUCCESS);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	parse_main(&info, fd);
	mlx_main(&info);
	exit(EXIT_SUCCESS);
}
