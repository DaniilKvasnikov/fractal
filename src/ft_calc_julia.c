/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:49:42 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 04:25:32 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_julia.h"
#include <pthread.h>

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

	value = ft_get_idx(block.z, block.r2, block.d, block.max_iter) - 1;
	val = value / (double)block.max_iter;
	return (ft_get_color_julia(data, val));
}

void		*thread_fun_j(void *point)
{
	int				index[2];
	float			z[2];
	float			step[2];
	float			min[2];
	t_julia_bloc	*bloc;

	bloc = (t_julia_bloc *)point;
	min[X_P] = bloc->data->display->global_x - (bloc->r[0] / bloc->dw);
	min[Y_P] = bloc->data->display->global_y - (bloc->r[0] / bloc->dw);
	step[X_P] = fabsf((2 * (bloc->r[0] / bloc->dw))) / (float)(WIN_W);
	step[Y_P] = fabsf((2 * (bloc->r[0] / bloc->dw))) / (float)(WIN_H);
	index[0] = -1;
	while (++index[0] < (WIN_W))
	{
		index[1] = (bloc->part / (float)bloc->all) * WIN_W - 1;
		while (++index[1] < (((bloc->part + 1) / (float)bloc->all) * WIN_W))
		{
			z[X_P] = min[X_P] + index[0] * step[X_P];
			z[Y_P] = min[Y_P] + index[1] * step[Y_P];
			bloc->xy_idx[index[0] + index[1] * (WIN_W)] = body_julia(bloc->data,
			initblock(z, bloc->r[1], bloc->d, bloc->data->display->max_iter));
		}
	}
	return (NULL);
}

int						*ft_calc_julia(t_julia_bloc *bloc)
{
	int					size;
	int					index;
	pthread_t			*tid;
	t_julia_bloc		*blocks;

	if ((bloc->xy_idx = (int *)malloc(sizeof(int) * WIN_W * WIN_H)) == 0)
		return (0);
	size = 128;
	bloc->all = size;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * size);
	blocks = (t_julia_bloc *)malloc(sizeof(t_julia_bloc) * size);
	index = -1;
	while (++index < size)
	{
		blocks[index] = *bloc;
		blocks[index].part = index;
		(void)pthread_create(&tid[index], NULL, thread_fun_j, &blocks[index]);
	}
	index = -1;
	while (++index < size)
		pthread_join(tid[index], NULL);
	free(tid);
	free(blocks);
	return (bloc->xy_idx);
}
