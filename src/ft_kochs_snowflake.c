/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kochs_snowflake.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 05:51:04 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/17 00:48:56 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_kochs.h"

static void		set(double *p, double x, double y)
{
	p[X_P] = x;
	p[Y_P] = y;
}

static t_kochs	inkochs(double *p1, double *p2, double *p3)
{
	t_kochs obj;

	set(obj.p1, p1[X_P], p1[Y_P]);
	set(obj.p2, p2[X_P], p2[Y_P]);
	set(obj.p3, p3[X_P], p3[Y_P]);
	return (obj);
}

static void		drawlines(t_data *data, t_kochs kochs, int iter)
{
	int color;

	if (data->display->colors == 1)
		color = 0xff0000 + iter * 25;
	else
		color = 0x0f0f00 + iter * 25;
	line_fast(data, kochs.p1, kochs.p2, color);
	line_fast(data, kochs.p2, kochs.p3, color);
}

static void		fractal(t_data *data, t_kochs kochs, int iter)
{
	double p4[2];
	double p5[2];
	double ps[2];
	double pn[2];

	if ((iter <= 0) || ((abs((int)(kochs.p1[X_P] - kochs.p2[X_P])) +
		abs((int)(kochs.p2[X_P] - kochs.p3[X_P]))) < 10))
		return ;
	set(p4, (kochs.p2[X_P] + 2 * kochs.p1[X_P]) / 3,
	(kochs.p2[Y_P] + 2 * kochs.p1[Y_P]) / 3);
	set(p5, (2 * kochs.p2[X_P] + kochs.p1[X_P]) / 3,
	(kochs.p1[Y_P] + 2 * kochs.p2[Y_P]) / 3);
	set(ps, (kochs.p2[X_P] + kochs.p1[X_P]) / 2,
	(kochs.p2[Y_P] + kochs.p1[Y_P]) / 2);
	set(pn, (4 * ps[X_P] - kochs.p3[X_P]) / 3,
	(4 * ps[Y_P] - kochs.p3[Y_P]) / 3);
	drawlines(data, inkochs(p4, pn, p5), ((iter * 0x000010) % 0xffffff));
	fractal(data, inkochs(p4, pn, p5), iter - 1);
	fractal(data, inkochs(pn, p5, p4), iter - 1);
	set(ps, (2 * kochs.p1[X_P] + kochs.p3[X_P]) / 3,
	(2 * kochs.p1[Y_P] + kochs.p3[Y_P]) / 3);
	set(pn, (2 * kochs.p2[X_P] + kochs.p3[X_P]) / 3,
	(2 * kochs.p2[Y_P] + kochs.p3[Y_P]) / 3);
	fractal(data, inkochs(kochs.p1, p4, ps), iter - 1);
	fractal(data, inkochs(p5, kochs.p2, pn), iter - 1);
}

void			ft_kochs_snowflake(t_data *data)
{
	double point1[2];
	double point2[2];
	double point3[2];
	double scale;

	scale = data->display->scale;
	point1[X_P] = WIN_W2 - 400 * scale;
	point1[Y_P] = WIN_H2 - 400 * scale;
	point2[X_P] = WIN_W2;
	point2[Y_P] = WIN_H2 + 10 * scale;
	point3[X_P] = WIN_W2 + 400 * scale;
	point3[Y_P] = WIN_H2 - 400 * scale;
	line_fast(data, point1, point2, 0xffffff);
	line_fast(data, point2, point3, 0xffffff);
	line_fast(data, point3, point1, 0xffffff);
	fractal(data, inkochs(point1, point2, point3),
	data->display->max_iter / 10);
	fractal(data, inkochs(point2, point3, point1),
	data->display->max_iter / 10);
	fractal(data, inkochs(point3, point1, point2),
	data->display->max_iter / 10);
}
