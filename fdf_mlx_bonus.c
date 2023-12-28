/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mlx_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:39:38 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/28 17:19:04 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	reset_img(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < MLX_SIZE_X)
	{
		j = 0;
		while (j < MLX_SIZE_Y)
		{
			my_mlx_pixel_put(img, i, j, 0x00000000);
			j++;
		}
		i++;
	}
}

int	set_ratio(t_info *info)
{
	double	max_diagonal;
	double	max_height;
	double	height_plat_ratio;

	max_diagonal = sqrt(pow(info->y_size, 2) + pow(info->x_size, 2));
	max_height = info->top_height - info->bottom_height;
	height_plat_ratio = 5;
	if (max_height > max_diagonal)
		height_plat_ratio = 5 * max_height / max_diagonal;
	info->plat_ratio = ((MLX_SIZE_X * 2) / (3 * max_diagonal));
	if (info->plat_ratio > 50)
		info->plat_ratio = 50;
	info->height_ratio = (info->plat_ratio / height_plat_ratio);
	if (info->height_ratio < 0.000001)
		info->height_ratio = 0.000001;
	info->min_x = 0;
	info->min_y = 0;
	info->max_x = MLX_SIZE_X - 1;
	info->max_y = MLX_SIZE_Y - 1;
	return (1);
}

void	set_valid_tran(t_info *info)
{
	if (info->min_x < 0)
		info->tran_x = -info->min_x;
	if (info->max_x > MLX_SIZE_X - 1)
		info->tran_x = -(info->max_x - MLX_SIZE_X + 1);
	if (info->min_y < 0)
		info->tran_y = -info->min_y;
	if (info->max_y > MLX_SIZE_Y - 1)
		info->tran_y = -(info->max_y - MLX_SIZE_Y + 1);
}

void	tran_model(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->y_size)
	{
		j = 0;
		while (j < info->x_size)
		{
			info->points[i][j].tran_x = \
				info->tran_x + info->points[i][j].x;
			info->points[i][j].tran_y = \
				info->tran_y + info->points[i][j].y;
			j++;
		}
		i++;
	}
}

void	mlx_main(t_info *info)
{
	t_data	img;

	info->mlx = mlx_init();
	info->mlx_win = mlx_new_window(info->mlx, MLX_SIZE_X, MLX_SIZE_Y, "fdf");
	img.img = mlx_new_image(info->mlx, MLX_SIZE_X, MLX_SIZE_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
									&img.line_length, &img.endian);
	info->img = &img;
	info->x_theta = 0;
	info->y_theta = 0;
	info->z_theta = 0;
	info->project_x_theta = M_PI / 6;
	info->project_y_theta = M_PI / 6;
	set_ratio(info);
	apply_ratio_rotate(info);
	set_valid_tran(info);
	tran_model(info);
	put_whole_img_window(&img, info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, img.img, 0, 0);
	mlx_hook(info->mlx_win, 2, 0, &key, info);
	mlx_hook(info->mlx_win, 17, 0, &mlx_exit, info);
	mlx_loop(info->mlx);
}
