/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:37:57 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 20:03:05 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x_axis(t_point *point, double theta)
{
	int	new_x;
	int	new_y;
	int	new_z;

	new_x = point->x;
	new_y = point->y * cos(theta) + point->z * sin(theta);
	new_z = -point->y * sin(theta) + point->z * cos(theta);
	point->x = new_x;
	point->y = new_y;
	point->z = new_z;
}

void	rotate_y_axis(t_point *point, double theta)
{
	int	new_x;
	int	new_y;
	int	new_z;

	new_x = point->x * cos(theta) - point->z * sin(theta);
	new_y = point->y;
	new_z = point->x * sin(theta) + point->z * cos(theta);
	point->x = new_x;
	point->y = new_y;
	point->z = new_z;
}

void	rotate_z_axis(t_point *point, double theta)
{
	int	new_x;
	int	new_y;
	int	new_z;

	new_x = point->x * cos(theta) + point->y * sin(theta);
	new_y = -point->x * sin(theta) + point->y * cos(theta);
	new_z = point->z;
	point->x = new_x;
	point->y = new_y;
	point->z = new_z;
}

void	apply_ratio_rotate(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->y_size)
	{
		j = 0;
		while (j < info->x_size)
		{
			info->points[i][j].x = \
				info->points[i][j].origin_x * info->plat_ratio;
			info->points[i][j].y = \
				info->points[i][j].origin_y * info->plat_ratio;
			info->points[i][j].z = \
				info->points[i][j].origin_z * info->height_ratio;
			rotate_x_axis(&info->points[i][j], info->x_theta);
			rotate_y_axis(&info->points[i][j], info->y_theta);
			rotate_z_axis(&info->points[i][j], info->z_theta);
			project(info, &info->points[i][j], M_PI / 6);
			j++;
		}
		i++;
	}
}

void	project(t_info *info, t_point *point, double theta)
{
	double	new_x;
	double	new_y;

	new_x = point->x * cos(theta) - point->y * cos(theta);
	new_y = point->x * sin(theta) + point->y * sin(theta) - point->z;
	point->x = new_x;
	point->y = new_y;
	if (new_x < info->min_x)
		info->min_x = new_x;
	if (new_x > info->max_x)
		info->max_x = new_x;
	if (new_y < info->min_y)
		info->min_y = new_y;
	if (new_y > info->max_y)
		info->max_y = new_y;
}
