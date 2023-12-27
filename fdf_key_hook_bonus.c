/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:29:54 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/27 14:25:27 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	tran_key(t_info *info, int keycode)
{
	if (keycode == 123)
		info->tran_x += 10;
	if (keycode == 124)
		info->tran_x -= 10;
	if (keycode == 126)
		info->tran_y += 10;
	if (keycode == 125)
		info->tran_y -= 10;
	return (1);
}

int	rotate_key(t_info *info, int keycode)
{
	if (keycode == 7)
		info->x_theta += M_PI / 18;
	if (keycode == 16)
		info->y_theta += M_PI / 18;
	if (keycode == 6)
		info->z_theta += M_PI / 18;
	return (1);
}

int	ratio_key(t_info *info, int keycode)
{
	if (keycode == 24)
	{
		if (info->plat_ratio > 100)
		{
			ft_printf("Warning : max ratio reached\n");
			return (0);
		}
		info->height_ratio *= 1.1;
		info->plat_ratio *= 1.1;
	}
	if (keycode == 27)
	{
		info->height_ratio *= 0.9;
		info->plat_ratio *= 0.9;
	}
	return (1);
}

int	key(int keycode, t_info *info)
{
	int	has_change;

	if (keycode >= 123 && keycode <= 126)
		has_change = tran_key(info, keycode);
	if (keycode == 7 || keycode == 16 || keycode == 6)
		has_change = rotate_key(info, keycode);
	if (keycode == 24 || keycode == 27)
		has_change = ratio_key(info, keycode);
	if (keycode == 15)
	{
		info->x_theta = 0;
		info->y_theta = 0;
		info->z_theta = 0;
		has_change = set_ratio(info);
	}
	if (keycode == 53)
		mlx_exit(info);
	if (!has_change)
		return (0);
	reset_img(info->img);
	apply_ratio_rotate(info);
	tran_model(info);
	put_whole_img_window(info->img, info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img->img, 0, 0);
	return (1);
}

int	mlx_exit(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img->img);
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(EXIT_SUCCESS);
}
