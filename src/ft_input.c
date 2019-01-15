/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:22:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 03:45:48 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	getscale(int type, float scale)
{
	if (type == 0)
		return (scale);
	else if (type == 1)
		return (1 / scale);
	else if (type == 2)
		return (scale);
	else if (type == 3)
		return (1 / scale);
	return (1);
}

static void		change_color(int key, t_data *data)
{
	if (key == 18)
		data->display->colors = 1;
	else if (key == 19)
		data->display->colors = 2;
}

int				key_release(int key, t_data *data)
{
	float scale;

	if (key == 53)
		ft_close(data);
	else if (key == 49)
	{
		data->display->global_x = 0;
		data->display->global_y = 0;
		data->display->scale = 1;
		data->display->max_iter = 50;
	}
	scale = getscale(data->display->type, data->display->scale);
	data->display->max_iter += ((key == 69) - (key == 78)) * 10;
	data->display->max_iter += (key == 88) - (key == 92);
	data->display->global_x +=
		((key == 123) - (key == 124)) * (scale / 4.0);
	data->display->global_y +=
		((key == 126) - (key == 125)) * (scale / 4.0);
	data->display->max_iter =
		(data->display->max_iter > 0) * (data->display->max_iter - 10) + 10;
	change_color(key, data);
	clearwin(data);
	draw(data);
	return (1);
}

int				mouse_move(int x, int y, t_data *data)
{
	if (x >= 0 && x < WIN_W &&
		y >= 0 && y < WIN_H &&
		data->display->type == 1 &&
		data->display->scale == 1 &&
		data->display->global_x == 0 &&
		data->display->global_y == 0)
	{
		data->display->local_x = x;
		data->display->local_y = y;
		clearwin(data);
		draw(data);
	}
	return (0);
}

int				mouse_press(int button, int x, int y, t_data *data)
{
	float scale;

	clearwin(data);
	scale = getscale(data->display->type, data->display->scale);
	if (button == 5 || button == 4)
	{
		data->display->global_x -= ((x - WIN_W2) * scale) / (WIN_W2 / 2.0);
		data->display->global_y -= ((y - WIN_H2) * scale) / (WIN_H2 / 2.0);
		data->display->scale *= 1.0 +
			(button == 5 && data->display->type == 1) +
			(button == 4 && data->display->type == 0);
		data->display->scale /= 1.0 +
			(button == 4 && data->display->type == 1) +
			(button == 5 && data->display->type == 0);
	}
	else if (button == 1)
	{
		data->display->global_x -= ((x - WIN_W2) * scale) / (WIN_W2 / 2.0);
		data->display->global_y -= ((y - WIN_H2) * scale) / (WIN_H2 / 2.0);
	}
	draw(data);
	return (0);
}
