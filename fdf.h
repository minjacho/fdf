/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:33:12 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 19:28:09 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# define MLX_SIZE_X 1960
# define MLX_SIZE_Y 1080

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
	double	tran_x;
	double	tran_y;
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
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	int		x_size;
	int		y_size;
	t_point	**points;
	int		bottom_color;
	int		top_color;
	double	top_height;
	double	bottom_height;
	double	plat_ratio;
	double	height_ratio;
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	double	tran_x;
	double	tran_y;
	double	x_theta;
	double	y_theta;
	double	z_theta;
}	t_info;

/*fdf_printer.c*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	put_whole_img_window(t_data *img, t_info *info);

/*rotate.c*/
void	apply_ratio_rotate(t_info *info);
void	project(t_info *info, t_point *point, double theta);

/*parse.c*/
void	parse_main(t_info *info, int fd);

/*input_read.c*/
t_input	*read_file(int fd);

/*err_handle.c*/
void	exit_malloc_error(void);
void	exit_not_valid_input(void);
void	free_double_ptr(char **lists);

/*fdf_mlx.c*/
void	reset_img(t_data *img);
void	set_ratio(t_info *info);
void	set_valid_tran(t_info *info);
void	tran_model(t_info *info);
void	mlx_main(t_info *info);

/*fdf_bonus.c*/
int		key(int keycode, t_info *info);
int		mouse(void);

#endif
