/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:22 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 17:22:47 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_double_ptr(char **lists)
{
	int	idx;

	idx = 0;
	while (lists[idx])
	{
		free(lists[idx]);
		idx++;
	}
	free(lists);
}

void	exit_not_valid_input(void)
{
	const char	*err_str = "Invalid Input\n";

	write(2, err_str, ft_strlen(err_str));
	exit(EXIT_FAILURE);
}

void	exit_malloc_error(void)
{
	const char	*err_str = "Malloc Error\n";

	write(2, err_str, ft_strlen(err_str));
	exit(EXIT_FAILURE);
}
