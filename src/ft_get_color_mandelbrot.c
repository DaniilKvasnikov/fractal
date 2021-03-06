/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:41:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:17:59 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mandelbrot.h"

int	ft_get_color_mandelbrot(t_data *data, int n)
{
	if (data->display->colors == 1)
		return (0xffffff * ((n % 0xffffff)));
	return (0x0000ff + 0x100000 * (n % 25));
}
