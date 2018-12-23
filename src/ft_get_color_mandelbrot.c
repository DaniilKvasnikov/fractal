/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:41:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 01:41:49 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_get_color_mandelbrot(int n, int nmax)
{
	int	result;
	int colwidth;
	int coloffset;

	result = 0xffffff;
	colwidth = 666;
	coloffset = 3200;
	n = (n + coloffset) % (3 * colwidth);
	if (n == 0 || n == nmax)
		return (0xffffff);
	else if (n / colwidth == 0)
		return ((237 * n / colwidth) * 0x010000 +
		(11 + 244 * n / colwidth) * 0x000100 + (116 + 139 * n / colwidth));
	else if (n / colwidth == 1)
	{
		n -= colwidth;
		return ((238) * 0x010000 +
		(255 - 123 * n / colwidth) * 0x000100 + (255 - 253 * n / colwidth));
	}
	n -= 2 * colwidth;
	return ((239 - 239 * n / colwidth) * 0x010000 +
	(132 - 121 * n / colwidth) * 0x000100 + (2 + 114 * n / colwidth));
}
