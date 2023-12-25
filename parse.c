/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:26 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/25 16:30:31 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_axis_size(t_input *input, t_info *info)
{
	t_input	*tmp;

	info->x_size = input->size;
	info->y_size = 1;
	tmp = input->next;
	while (tmp)
	{
		if (tmp->size != info->x_size)
			return (-1);
		info->y_size++;
		tmp = tmp->next;
	}
	return (0);
}

void	init_point(t_info *info, int x, int y, t_input *tmp)
{
	info->points[y][x].origin_x = (double)(x * 2);
	info->points[y][x].origin_y = (double)(y * 2);
	info->points[y][x].origin_z = (double)(tmp->nums[x] * 5);
	if (info->top_height < tmp->nums[x] * 1)
		info->top_height = tmp->nums[x] * 1;
	if (info->bottom_height > tmp->nums[x] * 1)
		info->bottom_height = tmp->nums[x] * 1;
}

void	init_info(t_info *info, t_input *input)
{
	t_input	*tmp;
	int		i;
	int		j;

	info->points = (t_point **)malloc(sizeof(t_point *) * info->y_size);
	if (!info->points)
		exit(EXIT_FAILURE); // malloc error
	i = 0;
	tmp = input;
	while (i < info->y_size)
	{
		j = 0;
		info->points[i] = (t_point *)malloc(sizeof(t_point) * info->x_size);
		if (!info->points[i])
			exit(EXIT_FAILURE); //malloc error
		while (j < info->x_size)
		{
			init_point(info, j, i, tmp);
			j++;
		}
		tmp = tmp->next;
		i++;
	}
}

void	parse_main(t_info *info, int fd)
{
	t_input	*input;

	input = read_file(fd);
	info->bottom_height = 0;
	info->top_height = 0;
	info->bottom_color = 0x00FFFFFF;
	info->top_color = 0x00FFFF00;
	if (!input)
		exit(EXIT_SUCCESS);
	if (get_axis_size(input, info) < 0)
		exit(EXIT_FAILURE); // invalid input
	init_info(info, input);
}
