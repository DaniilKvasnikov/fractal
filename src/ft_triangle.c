/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 04:44:17 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:26:03 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	setadndraw(t_data *data, float *dot, float x, float y)
{
	dot[0] = x;
	dot[1] = y;
	ft_draw_px(data, dot[0], dot[1], 0xff0000);
}

int			ft_get_color_triangle(t_data *data, int n)
{
	if (data->display->colors == 1)
		return (0xffffff * ((n % 0xffffff)));
	return (0x0000ff + 0x100000 * (n % 25));
}

static void	body_triangle(t_data *data, float sc)
{
	int			index;
	float		dot[2];
	float		*dots_;
	int			next;

	if ((dots_ = (float	*)malloc(sizeof(float) * 2 * 3)) == 0)
		return ;
	index = -1;
	setadndraw(data, &dots_[0], WIN_W2 - 500 * sc, WIN_H2 - 500 * sc);
	setadndraw(data, &dots_[2], WIN_W2, WIN_H2 + 499 * sc);
	setadndraw(data, &dots_[4], WIN_W2 + 500 * sc, WIN_H2 - 500 * sc);
	dot[X_P] = WIN_W2;
	dot[Y_P] = WIN_H2;
	index = -1;
	while (++index < (data->display->max_iter * 100000))
	{
		ft_draw_px(data, dot[X_P], dot[Y_P],
			ft_get_color_triangle(data, index));
		next = rand() % 3;
		dot[X_P] = (dot[X_P] + dots_[next * 2]) / 2;
		dot[Y_P] = (dot[Y_P] + dots_[next * 2 + 1]) / 2;
	}
}

void		ft_triangle(t_data *data)
{
	float sc;

	sc = data->display->scale;
	body_triangle(data, sc);
}
