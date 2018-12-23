/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:56:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/21 21:02:06 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <time.h>
#include <stdlib.h>

t_vertex	ft_vertex_init(float x, float y)
{
	t_vertex v;

	v.p[X_P] = x;
	v.p[Y_P] = y;
	return (v);
}

float		ft_com_mod(t_vertex *p)
{
	return (sqrt(p->p[X_P] * p->p[X_P] + p->p[Y_P] * p->p[Y_P]));
}

float		ft_com_mod2(t_vertex *p)
{
	return (p->p[X_P] * p->p[X_P] + p->p[Y_P] * p->p[Y_P]);
}

t_vertex	ft_com_sum(t_vertex *p1, t_vertex *p2)
{
	t_vertex v;

	v.p[X_P] = p1->p[X_P] + p2->p[X_P];
	v.p[Y_P] = p1->p[Y_P] + p2->p[Y_P];
	return (v);
}

float		ft_calc_r(t_vertex *p)
{
	return (1 + sqrt(1 + 4 * ft_com_mod(p)) / 2);
}

int			ft_get_idx(t_vertex *z0, float r, t_vertex *c, int n)
{
	t_vertex	res;
	float 		p[2];
	int			index;

	index = 1;
	res = ft_vertex_init(z0->p[X_P], z0->p[Y_P]);
	for (int i = 0; i < n; i++)
	{
		if (ft_com_mod2(&res) > r)
			break;
		p[X_P] = res.p[X_P] * res.p[X_P] - res.p[Y_P] * res.p[Y_P] + c->p[X_P];
		p[Y_P] = res.p[X_P] * res.p[Y_P] + res.p[X_P] * res.p[Y_P] + c->p[Y_P];
		res.p[X_P] = p[X_P];
		res.p[Y_P] = p[Y_P];
		index++;
	}
	return (index);
}

int ComplexHeatMap(int value, int min, int max, t_vertex z, double r)
{
	double val;

	val = (double)(value - min) / (double)(max - min);
	return ((0x010000 * 255 * val) +
			(0x000100 * 255 * (1 - val)) +
			(255 * (ft_com_mod2(&z) / r > 1 ? 1 : ft_com_mod2(&z) / r)));
}

void		ft_test(t_data *data, int maxIter, float dw, float dx)
{
	float		r;
	float		r2;
	t_vertex	c;
	float		min[2];
	float		max[2];
	float		step[2];
	t_vertex	z;
	int			i;
	int			j;
	int			idx;
	int			*xyIdx;

	if (dw < 1)
		return ;
	c = ft_vertex_init(dx, -0.11301);
	r = ft_calc_r(&c);
	if (r <= 0)
		return ;
	min[X_P] = -r / dw;
	min[Y_P] = -r / dw;
	max[X_P] = r / dw;
	max[Y_P] = r / dw;
	r2 = (r * r);
	step[X_P] = fabsf((max[X_P] - min[X_P])) / (float)(WIN_W);
	step[Y_P] = fabsf((max[Y_P] - min[Y_P])) / (float)(WIN_H);
	if ((xyIdx = (int *)malloc(sizeof(int) * WIN_W * WIN_H)) == 0)
		return ;
	i = -1;
	while (++i < (WIN_W))
	{
		j = -1;
		while (++j < (WIN_H2))
		{
			z.p[X_P] = min[X_P] + i * step[X_P];
			z.p[Y_P] = min[Y_P] + j * step[Y_P];
			idx = ft_get_idx(&z, r2, &c, maxIter) - 1;
			xyIdx[i + j * (WIN_W)] = idx;
			xyIdx[(WIN_W - i - 1) + (WIN_H - j - 1) * (WIN_W)] = idx;
		}
	}
	i = -1;
	while (++i < (WIN_W))
	{
		j = -1;
		while (++j < (WIN_H2))
		{
			z.p[X_P] = min[X_P] + i * step[X_P];
			z.p[Y_P] = min[Y_P] + j * step[Y_P];
			ft_draw_px(data, (WIN_W) - i - 1, j, ComplexHeatMap(xyIdx[i + j * (WIN_W)], 0, maxIter, z, r2));
			ft_draw_px(data, i, (WIN_H - j - 1), ComplexHeatMap(xyIdx[i + j * (WIN_W)], 0, maxIter, z, r2));
		}
	}
	free(xyIdx);
}

int			draw(t_data *data)
{
	if (data->img.img_ptr == NULL)
		data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIN_W, WIN_H);
	if (data->img.data == NULL)
		data->img.data = (int *)mlx_get_data_addr(data->img.img_ptr,
		&data->img.bpp, &data->img.size_l, &data->img.endian);
//	ft_triangle(data);
//	ft_test(data, 1000, data->scale, data->dx);
	frame(data, -0.743643900055, 0.131825890901, 0.000000049304);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win,
		data->img.img_ptr, 0, 0);
//	exit(0);
	return (1);
}

int			main(int argc, char **argv)
{
	srand(time(NULL));
	t_data	data;

	PRIN_RET((argc != 2), "usage: ./fdf source_file scale");
	data.scale = ft_atoi(argv[1]);
	data.dx = -0.75;
	if (((data.mlx_ptr = mlx_init()) == 0) ||
		((data.mlx_win =
		mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, argv[0])) == NULL))
		return (1);
	mlx_expose_hook(data.mlx_win, draw, &data);
	mlx_hook(data.mlx_win, 3, 1L << 3, key_release, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, mouse_move, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
