/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:49:42 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 10:58:08 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int				ft_get_idx(float *z0, float r, float *c, int n)
{
	float		res[2];
	float		temp;
	int			index;
	int			i;

	index = 1;
	res[0] = z0[X_P];
	res[1] = z0[Y_P];
	i = -1;
	while (++i < n)
	{
		if ((res[X_P] * res[X_P] + res[Y_P] * res[Y_P]) > r)
			break ;
		temp = res[X_P] * res[X_P] - res[Y_P] * res[Y_P] + c[X_P];
		res[Y_P] = res[X_P] * res[Y_P] +
			res[X_P] * res[Y_P] + c[Y_P];
		res[X_P] = temp;
		index++;
	}
	return (index);
}

static t_julia_block	initblock(float *z, float r2, float *d, int max_iter)
{
	t_julia_block block;

	block.z = z;
	block.r2 = r2;
	block.d = d;
	block.max_iter = max_iter;
	return (block);
}

static int				body_julia(t_data *data, t_julia_block block)
{
	double	val;
	int		value;
	int		min;

	min = 0;
	value = ft_get_idx(block.z, block.r2, block.d, block.max_iter) - 1;
	val = (double)(value - min) / (double)(block.max_iter - min);
	return (ft_get_color_julia(data, val, block.z, block.r2));
}

int						*ft_calc_julia(t_data *data, float *r,
										float *d, float dw)
{
	int			index[2];
	float		z[2];
	int			*xy_idx;
	float		step[2];
	float		min[2];

	min[X_P] = data->display->global_x - (r[0] / dw);
	min[Y_P] = data->display->global_y - (r[0] / dw);
	step[X_P] = fabsf((2 * (r[0] / dw))) / (float)(WIN_W);
	step[Y_P] = fabsf((2 * (r[0] / dw))) / (float)(WIN_H);
	if ((xy_idx = (int *)malloc(sizeof(int) * WIN_W * WIN_H)) == 0)
		return (0);
	index[0] = -1;
	while (++index[0] < (WIN_W))
	{
		index[1] = -1;
		while (++index[1] < (WIN_H))
		{
			z[X_P] = min[X_P] + index[0] * step[X_P];
			z[Y_P] = min[Y_P] + index[1] * step[Y_P];
			xy_idx[index[0] + index[1] * (WIN_W)] = body_julia(data,
					initblock(z, r[1], d, data->display->max_iter));
		}
	}
	return (xy_idx);
}
