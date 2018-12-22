/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:22:34 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/21 16:41:46 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int			key_release(int key, t_data *data)
{
	printf("key = %d\n", key);
	clearwin(data);
	if (key == 53)
		exit(0);
	else if (key == 0)
		data->iter -= 10;
	else if (key == 2)
		data->iter += 10;
	else if (key == 13)
		data->scale += 1;
	else if (key == 1)
		data->scale -= 1;
	printf("iter = %d\n", data->iter);
	printf("scale = %f\n", data->scale);
	draw(data);
	return (1);
}
