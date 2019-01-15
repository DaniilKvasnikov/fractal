/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 04:44:17 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 05:28:17 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_triangle.h"
#include <pthread.h>

static void	setadndraw(t_data *data, float *dot, float x, float y)
{
	dot[0] = x;
	dot[1] = y;
	ft_draw_px(data, dot[0], dot[1], 0xff0000);
}

int			ft_get_color_triangle(t_data *data, int n)
{
	if (data->display->colors == 1)
		return (0xffffff * ((n % 0xffffff)));
	return (0x0000ff + 0x100000 * (n % 25));
}

void		*thread_fun_t(void *point)
{
	int					index;
	int					next;
	t_triangle_block	*data;
	float				*dot;
	float				*dots_;

	data = (t_triangle_block *)point;
	dot = data->dot;
	dots_ = data->dots_;
	index = -1;
	while (++index < (data->data->display->max_iter * 100))
	{
		ft_draw_px(data->data, dot[X_P], dot[Y_P],
			ft_get_color_triangle(data->data, index));
		next = rand() % 3;
		dot[X_P] = (dot[X_P] + dots_[next * 2]) / 2;
		dot[Y_P] = (dot[Y_P] + dots_[next * 2 + 1]) / 2;
	}
	return (NULL);
}

static void	*body_triangle(void *block)
{
	int			index;
	float		dot[2];
	float		*dots_;
	float		sc;
	t_data		*data;

	if ((dots_ = (float	*)malloc(sizeof(float) * 2 * 3)) == 0)
		return (NULL);
	index = -1;
	sc = ((t_triangle_block *)block)->sc;
	data = ((t_triangle_block *)block)->data;
	setadndraw(data, &dots_[0], WIN_W2 - 500 * sc, WIN_H2 - 500 * sc);
	setadndraw(data, &dots_[2], WIN_W2, WIN_H2 + 499 * sc);
	setadndraw(data, &dots_[4], WIN_W2 + 500 * sc, WIN_H2 - 500 * sc);
	dot[X_P] = WIN_W2;
	dot[Y_P] = WIN_H2;
	((t_triangle_block *)block)->dot = dot;
	((t_triangle_block *)block)->dots_ = dots_;
	thread_fun_t(((t_triangle_block *)block));
	free(dots_);
	return (NULL);
}

void		ft_triangle(t_data *data)
{
	t_triangle_block	block;
	int					size;
	int					index;
	pthread_t			*tid;

	block.data = data;
	block.sc = data->display->scale;
	size = 128;
	tid = (pthread_t *)malloc(sizeof(pthread_t) * size);
	index = -1;
	while (++index < size)
		(void)pthread_create(&tid[index], NULL, body_triangle, &block);
	index = -1;
	while (++index < size)
		pthread_join(tid[index], NULL);
	free(tid);
}
