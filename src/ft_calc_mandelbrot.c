/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:45:19 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:16:00 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mandelbrot.h"

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
		y = 2 * x * y + q;
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

void		ft_calc_mandelbrot(t_data *data, t_mandelbrot_block block)
{
	double	dp;
	double	pq[2];
	int		index;
	int		i;
	int		j;

	index = -1;
	dp = block.range / (WIN_W - 1);
	j = -1;
	while (++j < WIN_H)
	{
		pq[1] = block.min[1] + j * dp;
		i = -1;
		while (++i < WIN_W)
		{
			pq[0] = block.min[0] + i * dp;
			block.pres[++index] = body_mandelbrot(data, pq, block.nmax);
		}
	}
}
