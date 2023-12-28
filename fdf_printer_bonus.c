/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_printer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:16:06 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/28 11:50:30 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (y < 0 || y >= MLX_SIZE_Y || x < 0 || x >= MLX_SIZE_X)
		return ;
	*(unsigned int *)dst = color;
}

int	get_color(t_info *info, t_point p1, t_point p2, double pct)
{
	double	z;
	int		color;

	z = (p2.origin_z - p1.origin_z) * pct + p1.origin_z;
	if (info->top_height - info->bottom_height == 0)
		color = info->bottom_color;
	else
		color = info->bottom_color + \
			(info->top_color - info->bottom_color) * \
				((z - info->bottom_height) / \
				(info->top_height - info->bottom_height));
	return (color);
}

static void	sub_put_line(t_data *img, t_point p1, t_point p2, t_info *info)
{
	double	x;
	double	y;

	x = p1.tran_x;
	y = p1.tran_y;
	if ((p2.tran_y - p1.tran_y) > (p2.tran_x - p1.tran_x))
	{
		while (y <= p2.tran_y)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y), \
			get_color(info, p1, p2, (y - p1.tran_y) / (p2.tran_y - p1.tran_y)));
			x += (p2.tran_x - p1.tran_x) / (p2.tran_y - p1.tran_y);
			y += 1;
		}
	}
	else
	{
		while (x <= p2.tran_x)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y), \
			get_color(info, p1, p2, (x - p1.tran_x) / (p2.tran_x - p1.tran_x)));
			x += 1;
			y += (p2.tran_y - p1.tran_y) / (p2.tran_x - p1.tran_x);
		}
	}
}

void	put_line_on_window(t_data *img, t_point p1, t_point p2, t_info *info)
{
	if (p1.tran_x < 0 && p2.tran_x < 0)
		return ;
	if (p1.tran_x >= MLX_SIZE_X && p2.tran_x >= MLX_SIZE_X)
		return ;
	if (p1.tran_y < 0 && p2.tran_y < 0)
		return ;
	if (p1.tran_y >= MLX_SIZE_Y && p2.tran_y >= MLX_SIZE_Y)
		return ;
	sub_put_line(img, p1, p2, info);
}

void	put_whole_img_window(t_data *img, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->y_size)
	{
		j = 0;
		while (j < info->x_size)
		{
			if (i != info->y_size - 1)
				put_line_on_window(img, info->points[i][j], \
									info->points[i + 1][j], info);
			if (j != info->x_size - 1)
				put_line_on_window(img, info->points[i][j], \
									info->points[i][j + 1], info);
			if (i != 0)
				put_line_on_window(img, info->points[i][j], \
									info->points[i - 1][j], info);
			if (j != 0)
				put_line_on_window(img, info->points[i][j], \
									info->points[i][j - 1], info);
			j++;
		}
		i++;
	}
}
