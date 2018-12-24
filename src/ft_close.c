/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:07:21 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 07:30:19 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(t_data *data)
{
	free(data->mlx_ptr);
	free(data->mlx_win);
	free(data->display);
	free(data->img.img_ptr);
	free(data->img.data);
	exit(0);
	return (0);
}
