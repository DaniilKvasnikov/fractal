/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:40:06 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/10 15:35:11 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JULIA_H
# define FT_JULIA_H

# include "fdf.h"

typedef struct	s_julia_block
{
	float	*z;
	float	r2;
	float	*d;
	int		max_iter;
}				t_julia_block;

int				*ft_calc_julia(t_data *data, float *r, float *d, float dw);
int				ft_get_color_julia(t_data *data,
					double val);

#endif
