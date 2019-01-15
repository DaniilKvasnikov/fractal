/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 04:58:09 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/15 05:11:41 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRIANGLE_H
# define FT_TRIANGLE_H

# include "fdf.h"

typedef struct	s_triangle_block
{
	t_data		*data;
	float		*dot;
	float		*dots_;
	float		sc;
	int			all;
	int			part;
}				t_triangle_block;

#endif
