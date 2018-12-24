/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_heart.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 01:17:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 05:08:53 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_draw_px(t_data *env, int x, int y, int color)
{
	float z;

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

	index = -1;
	size = WIN_W * WIN_H;
	while (++index < size)
		data->img.data[index] = 0x000000;
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
}

static void	draw_status(t_data *data)
{
	mlx_string_put(data->mlx_ptr, data->mlx_win, 0, 0, 0xffffff, "scale=");
	if (data->display->scale >= 1)
		mlx_string_put(data->mlx_ptr, data->mlx_win, 60, 0, 0xffffff,
			ft_itoa(data->display->scale));
	else
	{
		mlx_string_put(data->mlx_ptr, data->mlx_win, 60, 0, 0xffffff, "1/");
		mlx_string_put(data->mlx_ptr, data->mlx_win, 80, 0, 0xffffff,
			ft_itoa(1 / data->display->scale));
	}
	mlx_string_put(data->mlx_ptr, data->mlx_win, 0, 20, 0xffffff, "iter=");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 50, 20, 0xffffff,
		ft_itoa(data->display->max_iter));
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
	ft_draw_px(data, WIN_W2, WIN_H2, 0xff0000);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
	draw_status(data);
	return (1);
}
