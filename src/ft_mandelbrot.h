/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 11:08:36 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 03:48:19 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MANDELBROT_H
# define FT_MANDELBROT_H

# include "fdf.h"

typedef struct	s_mandelbrot_block
{
	double	range;
	double	*min;
	int		nmax;
	int		*pres;
	int		all;
	int		part;
	t_data	*data;
}				t_mandelbrot_block;

void			ft_calc_mandelbrot(t_mandelbrot_block *block);
int				ft_get_color_mandelbrot(t_data *data, int n);

#endif
