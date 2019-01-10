/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 20:07:21 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 09:06:38 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_ptrdel(void *ap)
{
	if (ap == NULL)
		return ;
	free(ap);
}

int			ft_close(t_data *data)
{
	ft_ptrdel(data->mlx_ptr);
	ft_ptrdel(data->mlx_win);
	ft_ptrdel(data->display);
	ft_ptrdel(data->img.img_ptr);
	ft_ptrdel(data->img.data);
	exit(0);
	return (0);
}
