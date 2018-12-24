/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:42:38 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 09:18:37 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_get_color_julia(int value, int max, float *p, double r)
{
	double	val;
	int		min;
	double	b;

	min = 0;
	b = (p[X_P] * p[X_P] + p[Y_P] * p[Y_P]) / r;
	val = (double)(value - min) / (double)(max - min);
	return ((0x010000 * 255 * val) +
			(0x000100 * 255 * (1 - val)) +
			(255 * (b > 1 ? 1 : b)));
}
