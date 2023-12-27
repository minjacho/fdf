/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:29:54 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/27 14:30:19 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key(int keycode, t_info *info)
{
	if (keycode == 53)
		mlx_exit(info);
	return (1);
}

int	mlx_exit(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img->img);
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(EXIT_SUCCESS);
}
