/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 19:37:57 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/25 15:55:20 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x_axis(t_point *point, double theta)
{
	int	new_x;
	int	new_y;
	int	new_z;

	new_x = point->origin_x * cos(theta) - point->origin_z * sin(theta);
	new_y = point->origin_y;
	new_z = point->origin_x * sin(theta) + point->origin_z * cos(theta);
	point->x = new_x;
	point->y = new_y;
	point->z = new_z;
}
void	rotate_y_axis(t_point *point, double theta)
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
void	rotate(t_point *point)
{
	rotate_x_axis(point, 0);
	rotate_y_axis(point, 0);
	rotate_z_axis(point, 0);
}

void	project(t_point *point, double theta)
{
	double	new_x;
	double	new_y;

	new_x = point->x * cos(theta) - point->y * cos(theta);
	new_y = point->x * sin(theta) + point->y * sin(theta) - point->z;
	point->x = new_x;
	point->y = new_y;
}
