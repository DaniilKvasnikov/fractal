/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:22:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 00:00:20 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int			key_release(int key, t_data *data)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit(0);
	return (1);
}

int			mouse_move(int x, int y, t_data *data)
{
	printf("x=%d y=%d\n", x, y);
	data->display->local_x = x;
	data->display->local_y = y;
	if (x >= 0 && x < WIN_W &&
		y >= 0 && y < WIN_H &&
		data->display->type == 1)
	{
		clearwin(data);
		draw(data);
	}
	return (0);
}
