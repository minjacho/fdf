/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:29:54 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 19:43:36 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	tran_key(t_info *info, int keycode)
{
	if (keycode == 123)
		info->tran_x += 10;
	if (keycode == 124)
		info->tran_x -= 10;
	if (keycode == 126)
		info->tran_y += 10;
	if (keycode == 125)
		info->tran_y -= 10;
}

void	rotate_key(t_info *info, int keycode)
{
	if (keycode == 7)
		info->x_theta += M_PI / 18;
	if (keycode == 16)
		info->y_theta += M_PI / 18;
	if (keycode == 6)
		info->z_theta += M_PI / 18;
}

void	ratio_key(t_info *info, int keycode)
{
	if (keycode == 24)
	{
		info->height_ratio *= 1.1;
		info->plat_ratio *= 1.1;
	}
	if (keycode == 27)
	{
		info->height_ratio *= 0.9;
		info->plat_ratio *= 0.9;
	}
}

int	key(int keycode, t_info *info)
{
	if (keycode >= 123 && keycode <= 126)
		tran_key(info, keycode);
	if (keycode == 7 || keycode == 16 || keycode == 6)
		rotate_key(info, keycode);
	if (keycode == 24 || keycode == 27)
		ratio_key(info, keycode);
	if (keycode == 15)
	{
		info->x_theta = 0;
		info->y_theta = 0;
		info->z_theta = 0;
		set_ratio(info);
	}
	if (keycode == 53)
		exit(0);
	reset_img(info->img);
	apply_ratio_rotate(info);
	tran_model(info);
	put_whole_img_window(info->img, info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img->img, 0, 0);
	return (1);
}

int	mouse(void)
{
	exit(0);
}
