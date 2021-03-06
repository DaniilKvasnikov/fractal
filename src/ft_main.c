/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:56:16 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/17 00:41:40 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_type(char *str)
{
	if (!(ft_strcmp("MANDELBROT", str)) || !(ft_strcmp("-M", str)))
		return (0);
	else if (!(ft_strcmp("JULIA", str)) || !(ft_strcmp("-J", str)))
		return (1);
	else if (!(ft_strcmp("TRIANGLE", str)) || !(ft_strcmp("-T", str)))
		return (2);
	else if (!(ft_strcmp("KOCHS", str)) || !(ft_strcmp("-K", str)))
		return (3);
	else if (!(ft_strcmp("TREE", str)) || !(ft_strcmp("-T", str)))
		return (4);
	else
	{
		ft_putendl("usage: ./fractol ...");
		ft_putendl("eg:\n\tMANDELBROT\n\tJULIA\n\tTRIANGLE\n\tKOCHS\n\tTREE");
		return (-1);
	}
}

static void	start_par(t_data *data, int type)
{
	data->display->type = type;
	data->display->local_x = WIN_W2;
	data->display->local_y = WIN_H2;
	data->display->global_x = 0;
	data->display->global_y = 0;
	data->display->scale = 1;
	data->display->max_iter = 50;
	data->display->colors = 1;
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		type;

	PRIN_RET((argc != 2),
	"usage: ./fractol ...\neg:\n\tMANDELBROT\n\tJULIA\n\tTRIANGLE\
	\n\tKOCHS\n\tTREE");
	if ((type = get_type(ft_toupper_str(argv[1]))) == -1)
		return (0);
	if (((data.mlx_ptr = mlx_init()) == 0) ||
		((data.mlx_win =
		mlx_new_window(data.mlx_ptr, WIN_W, WIN_H, argv[1])) == NULL) ||
		((data.display = (t_display *)malloc(sizeof(t_display))) == NULL))
		return (1);
	start_par(&data, type);
	mlx_expose_hook(data.mlx_win, draw, &data);
	mlx_hook(data.mlx_win, 3, 1L << 3, key_release, &data);
	mlx_hook(data.mlx_win, 4, 1L << 4, mouse_press, &data);
	mlx_hook(data.mlx_win, 6, 1L << 6, mouse_move, &data);
	mlx_hook(data.mlx_win, 17, 1L << 17, ft_close, &data);
	mlx_loop(data.mlx_ptr);
	ft_close(&data);
	return (0);
}
