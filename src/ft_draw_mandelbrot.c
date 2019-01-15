/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_mandelbrot.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:37:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 02:13:18 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mandelbrot.h"

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
			ft_draw_px(data, i, j, pres[++index]);
	}
}

static void	mandelbrot(t_data *data, double *min, double range, int nmax)
{
	int					*pres;
	t_mandelbrot_block	block;

	if ((pres = (int *)malloc(sizeof(int) * WIN_W * WIN_H)) == NULL)
		return ;
	block.range = range;
	block.min = min;
	block.nmax = nmax;
	block.pres = pres;
	block.data = data;
	ft_calc_mandelbrot(&block);
	draw_mandelbrot(data, pres);
	free(pres);
}

void		ft_draw_mandelbrot(t_data *data)
{
	double	center[2];
	double	min[2];
	double	range;

	center[0] = data->display->global_y / 2;
	center[1] = -data->display->global_x / 2;
	range = data->display->scale;
	min[0] = center[0] - range;
	min[1] = center[1] - range;
	mandelbrot(data, min, 2 * range, data->display->max_iter);
}
