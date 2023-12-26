/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:47:59 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 22:14:58 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_info	info;

	if (argc != 2)
		exit_not_valid_input();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_not_valid_input();
	parse_main(&info, fd);
	mlx_main(&info);
	exit(EXIT_SUCCESS);
}
