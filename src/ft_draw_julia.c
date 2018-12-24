/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:36:22 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 04:42:38 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	float		r[2];
	int			*xy_idx;

	r[0] = ft_calc_r(d);
	r[1] = (r[0] * r[0]);
	xy_idx = ft_calc_julia(data, r, d, dw);
	draw_julia(data, xy_idx);
	free(xy_idx);
}

void			ft_draw_julia(t_data *data)
{
	float d[2];

	d[X_P] = (data->display->local_x - WIN_W2) / (float)WIN_W2;
	d[Y_P] = (data->display->local_y - WIN_H2) / (float)WIN_H2;
	julia(data, data->display->scale, d);
}
