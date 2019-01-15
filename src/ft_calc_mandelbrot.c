/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:45:19 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 03:27:12 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mandelbrot.h"
#include <pthread.h>

static int	ft_get_idx(int nmax, double p, double q)
{
	double	x;
	double	y;
	double	xtemp;
	int		n;

	x = 0;
	y = 0;
	n = 0;
	while (n < nmax && (x * x) + (y * y) < 4)
	{
		xtemp = (x * x) - (y * y) + p;
		y = 2.0 * x * y + q;
		x = xtemp;
		n++;
	}
	return (n);
}

static int	body_mandelbrot(t_data *data, double *pq, int nmax)
{
	double	cardio;
	int		res;

	cardio = sqrt((pq[0] - 0.25) * (pq[0] - 0.25) + pq[1] * pq[1]);
	if (pq[0] < (cardio - 2 * cardio * cardio + 0.25) ||
		(pq[0] + 1) * (pq[0] + 1) + pq[1] * pq[1] < 0.0625)
		return (0x000000);
	else
	{
		res = ft_get_idx(nmax, pq[0], pq[1]);
		return ((res < nmax) *
		ft_get_color_mandelbrot(data, ft_get_idx(nmax, pq[0], pq[1])));
	}
}

void		*thread_fun(void *point)
{
	t_mandelbrot_block	*block;
	double				dp;
	double				pq[2];
	int					index[2];
	int					boundaries[2];

	block = (t_mandelbrot_block *)point;
	boundaries[0] = (block->part / (float)block->all) * WIN_W - 1;
	boundaries[1] = ((block->part + 1) / (float)block->all) * WIN_W;
	dp = block->range / (WIN_W - 1);
	index[1] = -1;
	while (++index[1] < WIN_H)
	{
		pq[1] = block->min[1] + index[1] * dp;
		index[0] = boundaries[0];
		while (++index[0] < boundaries[1])
		{
			pq[0] = block->min[0] + index[0] * dp;
			block->pres[index[1] * WIN_W + index[0]] =
			body_mandelbrot(block->data, pq, block->nmax);
		}
	}
	return (NULL);
}

void		ft_calc_mandelbrot(t_mandelbrot_block *block)
{
	int					size;
	int					index;
	pthread_t			*tid;
	t_mandelbrot_block	*blocks;

	size = 128;
	block->all = size;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * size);
	blocks = (t_mandelbrot_block *)malloc(sizeof(t_mandelbrot_block) * size);
	index = -1;
	while (++index < size)
	{
		blocks[index] = *block;
		blocks[index].part = index;
		(void)pthread_create(&tid[index], NULL, thread_fun, &blocks[index]);
	}
	index = -1;
	while (++index < size)
		pthread_join(tid[index], NULL);
	free(tid);
	free(blocks);
}
