/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:53:51 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/21 15:03:02 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_triangle(t_data *data)
{
	int			index;
	t_vertex	dot;
	t_vertex	*dots_;
	int			next;

	if ((dots_ = (t_vertex	*)malloc(sizeof(t_vertex) * DOTS)) == 0)
		return ;
	index = -1;
	while (++index < DOTS)
	{
		dots_[index] = ft_vertex_init(rand() % WIN_W, rand() % WIN_H);
		ft_draw_vertex(data, (dots_ + index), 0xff0000);
	}
	dot = ft_vertex_init(400, 150);
	index = -1;
	while (++index < 10000000)
	{
		ft_draw_vertex(data, &dot, 0xffffff);
		next = rand() % DOTS;
		dot.p[X_P] = (dot.p[X_P] + dots_[next].p[X_P]) / 2;
		dot.p[Y_P] = (dot.p[Y_P] + dots_[next].p[Y_P]) / 2;
	}
}
