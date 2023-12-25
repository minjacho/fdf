/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:33:12 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/25 16:30:05 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# define MLX_SIZE_X 3000
# define MLX_SIZE_Y 1500

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	double	origin_x;
	double	origin_y;
	double	origin_z;
}	t_point;

typedef struct s_input
{
	int				*nums;
	int				size;
	struct s_input	*next;
}	t_input;

typedef struct s_info
{
	int		x_size;
	int		y_size;
	t_point	**points;
	int		bottom_color;
	int		top_color;
	double	top_height;
	double	bottom_height;
}	t_info;

void	put_line_on_window(t_data *img, t_point p1, t_point p2, t_info *info);
void	rotate(t_point *point);
void	project(t_point *point, double theta);
void	free_double_ptr(char **lists);

void	parse_main(t_info *info, int fd);

t_input	*read_file(int fd);

#endif
