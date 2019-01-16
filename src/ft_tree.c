/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 00:00:32 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/17 00:39:35 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_drawtree_body(t_data *data, float *pos, double a, double angle)
{
	double	ang1;
	double	ang2;
	float	posnew[2];
	int		color;

	ang1 = M_PI * ((data->display->local_x - WIN_W2) / (float)WIN_W2);
	ang2 = M_PI * ((data->display->local_y - WIN_H2) / (float)WIN_H2);
	if (data->display->colors == 1)
		color = 0x00ff00;
	else
		color = a * (0x010100) + 0x0000ff;
	if (a > 2)
	{
		a *= 0.7;
		posnew[0] = pos[0] + a * cos(angle);
		posnew[1] = pos[1] + a * sin(angle);
		line_fast(data, pos, posnew, color);
		ft_drawtree_body(data, posnew, a, angle + ang1);
		ft_drawtree_body(data, posnew, a, angle - ang2);
	}
	return (0);
}

int			ft_drawtree(t_data *data)
{
	float	pos[2];
	float	a;
	float	angle;

	pos[0] = WIN_W2;
	pos[1] = 0;
	a = data->display->max_iter;
	angle = M_PI / 2;
	return (ft_drawtree_body(data, pos, a, angle));
}