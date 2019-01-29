/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:12:03 by rrhaenys          #+#    #+#             */
/*   Updated: 2019/01/17 00:10:37 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "ft_opencl.h"
# include <math.h>
# include <mlx.h>

# define WIN_W 1024
# define WIN_H 1024
# define WIN_W2 (WIN_W / 2)
# define WIN_H2 (WIN_H / 2)
# define WIN_S (WIN_W * WIN_H)
# define PRIN_RET(a,s) {if (a){ft_putendl(s); return (0);}}
# define X_P 0
# define Y_P 1
# define BLOCK_1(a, b, c, d) {a -= b; c += d;}
# define BLOCK_2(a, b, c, d, e) {if ((a += e) >= b) BLOCK_1(a, b, c, d);}
# define SGN(x) ((x < 0) ? -1 : ((x > 0) ? 1 : 0))

typedef struct	s_display
{
	int			local_x;
	int			local_y;
	double		scale;
	double		global_x;
	double		global_y;
	int			type;
	int			max_iter;
	int			colors;
}				t_display;

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
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		img;
	t_display	*display;
}				t_data;

typedef struct	s_vertex
{
	double		p[2];
}				t_vertex;

int				key_release(int key, t_data *data);
int				mouse_move(int x, int y, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				ft_close(t_data *data);
void			ft_draw_px(t_data *env, int x, int y, int color);
void			clearwin(t_data *data);
int				draw(t_data *data);
void			line_fast(t_data *env, double *p1, double *p2, int color);
void			ft_draw_mandelbrot(t_data *data);
void			ft_draw_julia(t_data *data);
void			ft_triangle(t_data *data);
void			ft_kochs_snowflake(t_data *data);
int				ft_drawtree(t_data *data);
void			testcl(void);

#endif
