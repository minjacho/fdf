/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:16:06 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/25 16:28:53 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	// printf("x = %d y = %d\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_info *info, t_point p1, t_point p2, double pct)
{
	double	z;
	int		color;

	z = (p2.origin_z - p1.origin_z) * pct + p1.origin_z;
	color = info->bottom_color + \
		(info->top_color - info->bottom_color) * \
			(z - info->bottom_height) / (info->top_height - info->bottom_height);
	return (color);
}

void	put_line_on_window(t_data *img, t_point p1, t_point p2, t_info *info)
{
	double	x;
	double	y;

	x = p1.x;
	y = p1.y;
	if ((p2.y - p1.y) > (p2.x - p1.x))
	{
		while (y <= p2.y)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y),\
				get_color(info, p1, p2, (y - p1.y) / (p2.y - p1.y)));
			x += (p2.x - p1.x) / (p2.y - p1.y);
			y += 1;
		}
	}
	else
	{
		while (x <= p2.x)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y),\
				get_color(info, p1, p2, (x - p1.x) / (p2.x - p1.x)));
			x += 1;
			y += (p2.y - p1.y) / (p2.x - p1.x);
		}
	}
}
