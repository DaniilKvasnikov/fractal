/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:37:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 01:46:29 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_mandelbrot(t_data *data, int *pres)
{
	int		i;
	int		j;
	int		index;

	i = -1;
	index = -1;
	while (++i < (WIN_W))
	{
		j = -1;
		while (++j < (WIN_H))
			ft_draw_px(data, j, i, pres[++index]);
	}
}

static void	mandelbrot(t_data *data, double *min, double range, int nmax)
{
	int		*pres;

	if ((pres = (int *)malloc(sizeof(int) * WIN_W * WIN_H)) == NULL)
		return ;
	ft_calc_mandelbrot(range, min, nmax, pres);
	draw_mandelbrot(data, pres);
	free(pres);
}

void		ft_draw_mandelbrot(t_data *data)
{
	double	center[2];
	double	min[2];
	double	range;

	center[0] = -1;
	center[1] = 0;
	range = 1;
	min[0] = center[0] - range / 2;
	min[1] = center[1] - range / 2.5;
	mandelbrot(data, min, 1, 1000);
}
