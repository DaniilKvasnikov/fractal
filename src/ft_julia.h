/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 10:40:06 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 11:23:59 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_JULIA_H
# define FT_JULIA_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

typedef struct	s_julia_block
{
	float	*z;
	float	r2;
	float	*d;
	int		max_iter;
}				t_julia_block;

#endif
