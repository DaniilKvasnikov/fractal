/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kochs_snowflake.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 05:51:04 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 07:21:47 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set(float *p, float x, float y)
{
	p[X_P] = x;
	p[Y_P] = y;
}

static t_kochs	inkochs(float *p1, float *p2, float *p3)
{
	t_kochs obj;

	set(obj.p1, p1[X_P], p1[Y_P]);
	set(obj.p2, p2[X_P], p2[Y_P]);
	set(obj.p3, p3[X_P], p3[Y_P]);
	return (obj);
}

static void		drawlines(t_data *data, t_kochs kochs)
{
	line_fast(data, kochs.p1, kochs.p2, 0xffffff);
	line_fast(data, kochs.p2, kochs.p3, 0xffffff);
	line_fast(data, kochs.p3, kochs.p1, 0xffffff);
}

static void		fractal(t_data *data, t_kochs kochs, int iter)
{
	float p4[2];
	float p5[2];
	float ps[2];
	float pn[2];

	if (iter > 0)
	{
		set(p4, (kochs.p2[X_P] + 2 * kochs.p1[X_P]) / 3,
		(kochs.p2[Y_P] + 2 * kochs.p1[Y_P]) / 3);
		set(p5, (2 * kochs.p2[X_P] + kochs.p1[X_P]) / 3,
		(kochs.p1[Y_P] + 2 * kochs.p2[Y_P]) / 3);
		set(ps, (kochs.p2[X_P] + kochs.p1[X_P]) / 2,
		(kochs.p2[Y_P] + kochs.p1[Y_P]) / 2);
		set(pn, (4 * ps[X_P] - kochs.p3[X_P]) / 3,
		(4 * ps[Y_P] - kochs.p3[Y_P]) / 3);
		drawlines(data, inkochs(p4, pn, p5));
		fractal(data, inkochs(p4, pn, p5), iter - 1);
		fractal(data, inkochs(pn, p5, p4), iter - 1);
		set(ps, (2 * kochs.p1[X_P] + kochs.p3[X_P]) / 3,
		(2 * kochs.p1[Y_P] + kochs.p3[Y_P]) / 3);
		set(pn, (2 * kochs.p2[X_P] + kochs.p3[X_P]) / 3,
		(2 * kochs.p2[Y_P] + kochs.p3[Y_P]) / 3);
		fractal(data, inkochs(kochs.p1, p4, ps), iter - 1);
		fractal(data, inkochs(p5, kochs.p2, pn), iter - 1);
	}
}

void			ft_kochs_snowflake(t_data *data)
{
	float point1[2];
	float point2[2];
	float point3[2];

	point1[X_P] = 100.0;
	point1[Y_P] = 300.0;
	point2[X_P] = WIN_W2;
	point2[Y_P] = WIN_H - 100;
	point3[X_P] = WIN_W - 100;
	point3[Y_P] = 300.0;
	line_fast(data, point1, point2, 0xffffff);
	line_fast(data, point2, point3, 0xffffff);
	line_fast(data, point3, point1, 0xffffff);
	fractal(data, inkochs(point1, point2, point3), 10);
	fractal(data, inkochs(point2, point3, point1), 10);
	fractal(data, inkochs(point3, point1, point2), 10);
}
