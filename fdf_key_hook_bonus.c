/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:29:54 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/28 17:20:02 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	tran_rotate_key(t_info *info, int keycode)
{
	if (keycode == 123)
		info->tran_x += 10;
	if (keycode == 124)
		info->tran_x -= 10;
	if (keycode == 126)
		info->tran_y += 10;
	if (keycode == 125)
		info->tran_y -= 10;
	if (keycode == 7)
		info->x_theta += M_PI / 36;
	if (keycode == 16)
		info->y_theta += M_PI / 36;
	if (keycode == 6)
		info->z_theta += M_PI / 36;
	return (1);
}

int	project_key(t_info *info, int keycode)
{
	if (keycode == 13)
	{
		info->project_x_theta -= M_PI / 36;
		info->project_y_theta -= M_PI / 36;
	}
	if (keycode == 1)
	{
		info->project_x_theta += M_PI / 36;
		info->project_y_theta += M_PI / 36;
	}
	if (keycode == 0)
	{
		info->project_x_theta -= M_PI / 36;
		info->project_y_theta += M_PI / 36;
	}
	if (keycode == 2)
	{
		info->project_x_theta += M_PI / 36;
		info->project_y_theta -= M_PI / 36;
	}
	return (1);
}

int	ratio_key(t_info *info, int keycode)
{
	if (keycode == 15)
	{
		info->x_theta = 0;
		info->y_theta = 0;
		info->z_theta = 0;
		info->project_x_theta = M_PI / 6;
		info->project_y_theta = M_PI / 6;
		set_ratio(info);
		return (1);
	}
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
	return (1);
}

int	key(int keycode, t_info *info)
{
	int	has_change;

	if ((keycode >= 123 && keycode <= 126) \
		|| (keycode == 7 || keycode == 16 || keycode == 6))
		has_change = tran_rotate_key(info, keycode);
	if (keycode == 13 || keycode == 1 || keycode == 0 || keycode == 2)
		has_change = project_key(info, keycode);
	if (keycode == 24 || keycode == 27 || keycode == 15)
		has_change = ratio_key(info, keycode);
	if (keycode == 53)
		mlx_exit(info);
	if (!has_change)
		return (0);
	reset_img(info->img);
	apply_ratio_rotate(info);
	if (keycode == 15)
		set_valid_tran(info);
	tran_model(info);
	put_whole_img_window(info->img, info);
	mlx_put_image_to_window(info->mlx, info->mlx_win, info->img->img, 0, 0);
	usleep(1000);
	return (1);
}

int	mlx_exit(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img->img);
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(EXIT_SUCCESS);
}
