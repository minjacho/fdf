/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:46:46 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/28 13:01:37 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_better_atod(const char *str)
{
	int		i;
	double	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		exit_not_valid_input();
	while (str[i] && ft_isdigit(str[i]))
	{
		num *= 10;
		num += (str[i] - '0') * sign;
		i++;
	}
	return (num);
}

char	*get_next_line_wo_nl(int fd)
{
	char	*line;
	char	*result;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	result = ft_strtrim(line, "\n");
	if (!result)
		exit_malloc_error();
	free(line);
	return (result);
}

int	get_one_line_input(int fd, double **nums)
{
	char	*line;
	char	**str_nums;
	int		size;
	int		idx;

	line = get_next_line_wo_nl(fd);
	if (!line)
		return (-1);
	str_nums = ft_split(line, ' ');
	if (!str_nums)
		exit_malloc_error();
	if (!str_nums[0])
		exit_not_valid_input();
	size = 0;
	while (str_nums[size])
		size++;
	*nums = (double *)malloc(sizeof(double) * size);
	idx = -1;
	while (++idx < size)
		(*nums)[idx] = ft_better_atod(str_nums[idx]);
	free(line);
	free_double_ptr(str_nums);
	return (size);
}

t_input	*make_new_node(int fd)
{
	double	*nums;
	int		size;
	t_input	*new_node;

	size = get_one_line_input(fd, &nums);
	if (size < 0)
		return (NULL);
	new_node = (t_input *)malloc(sizeof(t_input));
	if (!new_node)
		exit_malloc_error();
	new_node->nums = nums;
	new_node->size = size;
	new_node->next = NULL;
	return (new_node);
}

t_input	*read_file(int fd)
{
	t_input	*tmp;
	t_input	*start;

	start = make_new_node(fd);
	tmp = start;
	if (!tmp)
		exit_not_valid_input();
	while (tmp)
	{
		tmp->next = make_new_node(fd);
		tmp = tmp->next;
	}
	return (start);
}
