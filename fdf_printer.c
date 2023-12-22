/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_printer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 17:16:06 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/22 17:16:08 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_line_on_window(t_data *img, t_point p1, t_point p2)
{
	double	x;
	double	y;

	x = p1.x;
	y = p1.y;
	if ((p2.y - p1.y) > (p2.x - p1.x))
	{
		while (y <= p2.y)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y), 0x0000FF00);
			x += (p2.x - p1.x) / (p2.y - p1.y);
			y += 1;
		}
	}
	else
	{
		while (x <= p2.x)
		{
			my_mlx_pixel_put(img, (int)round(x), (int)round(y), 0x0000FF00);
			x += 1;
			y += (p2.y - p1.y) / (p2.x - p1.x);
		}
	}
}
