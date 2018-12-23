/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:56:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/23 23:32:09 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	t_data	data;

	PRIN_RET((argc != 2), "usage: ./fdf [MANDELBROT]/[JULIA]");
	if (((data.mlx_ptr = mlx_init()) == 0) ||
		((data.mlx_win =
		mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, argv[0])) == NULL) ||
		((data.display = (t_display *)malloc(sizeof(t_display))) == NULL))
		return (1);
	if (!(ft_strcmp("MANDELBROT", argv[1])))
		data.display->type = 0;
	else if (!(ft_strcmp("JULIA", argv[1])))
		data.display->type = 1;
	data.display->local_x = WIN_W2;
	data.display->local_y = WIN_H2;
	mlx_expose_hook(data.mlx_win, draw, &data);
	mlx_hook(data.mlx_win, 3, 1L << 3, key_release, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, mouse_move, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, mouse_move, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
