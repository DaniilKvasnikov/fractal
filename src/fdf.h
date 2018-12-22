/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:12:03 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/21 21:00:40 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

# define BLOCK_1(a, b, c, d) {a -= b; c += d;}
# define BLOCK_2(a, b, c, d, e) {if ((a += e) >= b) BLOCK_1(a, b, c, d);}
# define DEG_TO_RAD(deg) (M_PI * deg / 180)
# define RAD_TO_DEG(rad) (180 * rad / M_PI)
# define SGN(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))
# define PRIN_RET(a,s) {if (a){ft_putendl(s); return (0);}}
# define WIN_W 1024
# define WIN_H 1024
# define WIN_W2 (WIN_W / 2)
# define WIN_H2 (WIN_H / 2)
# define WIN_S (WIN_W * WIN_H)
# define BUF_SIZE 1024
# define X_P 0
# define Y_P 1
# define Z_P 2
# define N_P 3
# define DELTA_SCALE 0.1
# define MAX_H 250
# define MAX_SCALE 20
# define MIN_SCALE -1
# define DOTS 3

typedef struct	s_vertex
{
	float		p[2];
}				t_vertex;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_data
{
	void			*mlx_ptr;
	void			*mlx_win;
	t_img			img;
	float			scale;
	float			dx;
}				t_data;

int				draw(t_data *data);
void			ft_draw_px(t_data *env, int x, int y, int color);
void			ft_draw_vertex(t_data *data, t_vertex *dot, int color);
void			line_fast(t_data *env, float *p1, float *p2, int color);
void			clearwin(t_data *data);
int				key_release(int key, t_data *data);
int				mouse_move(int x, int y, t_data *data);
void			ft_triangle(t_data *data);
t_vertex		ft_vertex_init(float x, float y);

#endif
