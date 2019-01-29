/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:36:22 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 04:00:01 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_julia.h"

static float	ft_calc_r(float *p)
{
	return (1 + sqrt(1 + 4 *
	((sqrt(p[X_P] * p[X_P] + p[Y_P] * p[Y_P])))) / 2);
}

static void		draw_julia(t_data *data, int *xy_idx)
{
	int			i;
	int			j;

	i = -1;
	while (++i < (WIN_W))
	{
		j = -1;
		while (++j < (WIN_H))
		{
			ft_draw_px(data, (WIN_W) - i - 1, j, xy_idx[i + j * (WIN_W)]);
		}
	}
}

static void		julia(t_data *data, float dw, float *d)
{
	float			r[2];
	int				*xy_idx;
	t_julia_bloc	bloc;

	r[0] = ft_calc_r(d);
	r[1] = (r[0] * r[0]);
	bloc.data = data;
	bloc.r = r;
	bloc.d = d;
	bloc.dw = dw;
	xy_idx = ft_calc_julia(&bloc);
	draw_julia(data, xy_idx);
	free(xy_idx);
}

#include <stdio.h>

void	ft_test(int *buf1)
{
	const size_t size = 1024 * 1024;
	for(size_t i = 0; i < size; i++)
		buf1[i] = 0x00ff00;
	ft_opencl(buf1);
}


void			ft_draw_julia(t_data *data)
{
	ft_test(data->img.data);
	return ;
	float d[2];

	d[X_P] = (data->display->local_x - WIN_W2) / (float)WIN_W2;
	d[Y_P] = (data->display->local_y - WIN_H2) / (float)WIN_H2;
	julia(data, data->display->scale, d);
}
