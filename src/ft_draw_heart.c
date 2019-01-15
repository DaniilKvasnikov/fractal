/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 01:17:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 03:21:19 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_draw_px(t_data *env, int x, int y, int color)
{
	float z;

	if (env->img.size_l <= 100)
		return ;
	x = (int)(x);
	y = (int)(WIN_H - y - 1);
	z = x + (y * WIN_W);
	if (z >= 0 && z < WIN_S &&
		x >= 0 && x <= WIN_W &&
		y >= 0)
		env->img.data[y * WIN_W + x] = color;
}

void		clearwin(t_data *data)
{
	int index;
	int size;

	if (data->img.size_l <= 100)
		return ;
	index = -1;
	size = WIN_W * WIN_H;
	while (++index < size)
		data->img.data[index] = 0x000000;
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
}

void		line_fast(t_data *env, float *p1, float *p2, int color)
{
	int i;
	int x[2];
	int p[2];

	x[0] = abs((int)(p2[Y_P] - p1[Y_P])) >> 1;
	x[1] = abs((int)(p2[X_P] - p1[X_P])) >> 1;
	ft_draw_px(env, (p[0] = p1[X_P]),
				(p[1] = p1[Y_P]), color);
	if (((i = -1) == -1) && abs((int)(p2[X_P] - p1[X_P])) >=
		abs((int)(p2[Y_P] - p1[Y_P])))
		while (++i < abs((int)(p2[X_P] - p1[X_P])))
		{
			BLOCK_2(x[1], abs((int)(p2[X_P] - p1[X_P])), p[1],
			SGN(p2[Y_P] - p1[Y_P]), abs((int)(p2[Y_P] - p1[Y_P])));
			ft_draw_px(env, (p[0] += SGN(p2[X_P] - p1[X_P])), p[1], color);
		}
	else
		while (++i < abs((int)(p2[Y_P] - p1[Y_P])))
		{
			BLOCK_2(x[0], abs((int)(p2[Y_P] - p1[Y_P])), p[0],
			SGN(p2[X_P] - p1[X_P]), abs((int)(p2[X_P] - p1[X_P])));
			ft_draw_px(env, p[0], (p[1] += SGN(p2[Y_P] - p1[Y_P])), color);
		}
}

static void	draw_status(t_data *data)
{
	char	*str;
	int		color;

	color = 0xff0000;
	mlx_string_put(data->mlx_ptr, data->mlx_win, 0, 0, color, "scale=");
	if (data->display->scale >= 1)
		mlx_string_put(data->mlx_ptr, data->mlx_win, 60, 0, color,
			(str = ft_itoa(data->display->scale)));
	else
	{
		mlx_string_put(data->mlx_ptr, data->mlx_win, 60, 0, color, "1/");
		mlx_string_put(data->mlx_ptr, data->mlx_win, 80, 0, color,
			(str = ft_itoa(1 / data->display->scale)));
	}
	if (str != NULL)
		free(str);
	mlx_string_put(data->mlx_ptr, data->mlx_win, 0, 20, color, "iter=");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 50, 20, color,
		(str = ft_itoa(data->display->max_iter)));
	if (str != NULL)
		free(str);
}

int			draw(t_data *data)
{
	if (data->img.img_ptr == NULL)
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (data->img.data == NULL)
		data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr,
		&data->img.bpp, &data->img.size_l, &data->img.endian);
	if (data->display->type == 0)
		ft_draw_mandelbrot(data);
	else if (data->display->type == 1)
		ft_draw_julia(data);
	else if (data->display->type == 2)
		ft_triangle(data);
	else if (data->display->type == 3)
		ft_kochs_snowflake(data);
	if (data->img.size_l <= 100)
	{
		ft_putendl("Need more memory...");
		exit(0);
	}
	ft_draw_px(data, WIN_W2, WIN_H2, 0xff0000);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
	draw_status(data);
	return (1);
}
