/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 12:03:22 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/23 12:33:09 by minjacho         ###   ########.fr       */
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
