/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_color_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 01:42:38 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/10 15:34:02 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_julia.h"

int		ft_get_color_julia(t_data *data, double val)
{
	if (data->display->colors == 1)
	{
		return ((0x010000 * 255 * val) +
				(0x000100 * 255 * (1 - val)));
	}
	return (0x00ffff * val);
}
