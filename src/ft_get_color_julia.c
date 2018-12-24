/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:42:38 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:30:16 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_julia.h"

int		ft_get_color_julia(t_data *data, double val, float *p, double r)
{
	double	b;

	b = (p[X_P] * p[X_P] + p[Y_P] * p[Y_P]) / r;
	if (data->display->colors == 1)
	{
		return ((0x010000 * 255 * val) +
				(0x000100 * 255 * (1 - val)) +
				(255 * (b > 1 ? 1 : b)));
	}
	return (0x00ffff * val);
}
