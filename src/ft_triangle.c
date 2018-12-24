/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 04:44:17 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 05:09:07 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_triangle(t_data *data)
{
	int			index;
	float		dot[2];
	float		*dots_;
	int			next;

	if ((dots_ = (float	*)malloc(sizeof(float) * 2 * 3)) == 0)
		return ;
	index = -1;
	while (++index < 6)
	{
		dots_[index] = (rand() % WIN_W);
		dots_[++index] = (rand() % WIN_H);
		ft_draw_px(data, dots_[index - 1], dots_[index], 0xff0000);
	}
	dot[X_P] = WIN_W2;
	dot[Y_P] = WIN_H2;
	index = -1;
	while (++index < (data->display->max_iter * 150))
	{
		ft_draw_px(data, dot[X_P], dot[Y_P], 0xffffff);
		next = rand() % 3;
		dot[X_P] = (dot[X_P] + dots_[next * 2]) / 2;
		dot[Y_P] = (dot[Y_P] + dots_[next * 2 + 1]) / 2;
	}
}
