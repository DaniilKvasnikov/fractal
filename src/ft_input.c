/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:22:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:39:59 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		change_color(int key, t_data *data)
{
	if (key == 18)
		data->display->colors = 1;
	else if (key == 19)
		data->display->colors = 2;
}

int				key_release(int key, t_data *data)
{
	if (key == 53)
		exit(0);
	else if (key == 49)
	{
		data->display->global_x = 0;
		data->display->global_y = 0;
		data->display->scale = 1;
		data->display->max_iter = 50;
	}
	else if (key == 69)
		data->display->max_iter += 10;
	else if (key == 78)
		data->display->max_iter -= 10;
	else if (key == 88)
		data->display->max_iter += 1;
	else if (key == 92)
		data->display->max_iter -= 1;
	change_color(key, data);
	if (data->display->max_iter <= 0)
		data->display->max_iter = 10;
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

int				mouse_press(int button, int x, int y, t_data *data)
{
	float scale;

	clearwin(data);
	scale = getscale(data->display->type, data->display->scale);
	if (button == 5)
	{
		data->display->global_x -= 2 * ((x - WIN_W2) * scale) / (float)WIN_W2;
		data->display->global_y -= 2 * ((y - WIN_H2) * scale) / (float)WIN_W2;
		data->display->scale *= 2;
	}
	else if (button == 4)
		data->display->scale /= 2;
	else if (button == 1)
	{
		data->display->global_x -= 2 * ((x - WIN_W2) * scale) / (float)WIN_W2;
		data->display->global_y -= 2 * ((y - WIN_H2) * scale) / (float)WIN_W2;
	}
	draw(data);
	return (0);
}
