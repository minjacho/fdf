/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:26 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/23 14:43:11 by minjacho         ###   ########.fr       */
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

void	init_info(t_info *info, t_input *input)
{
	t_input	*tmp;
	int		i;
	int		j;

	info->points = (t_point **)malloc(sizeof(t_point *) * info->x_size);
	if (!info->points)
		exit(EXIT_FAILURE); // malloc error
	i = 0;
	tmp = input;
	while (i < info->y_size)
	{
		j = 0;
		info->points[i] = (t_point *)malloc(sizeof(t_point) * info->y_size);
		if (!info->points[i])
			exit(EXIT_FAILURE); //malloc error
		while (j < info->x_size)
		{
			info->points[i][j].x = j * 5;
			info->points[i][j].y = i * 5;
			info->points[i][j].z = tmp->nums[j];
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
	if (!input)
		exit(EXIT_SUCCESS);
	if (get_axis_size(input, info) < 0)
		exit(EXIT_FAILURE); // invalid input
	init_info(info, input);
}
