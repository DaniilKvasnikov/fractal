/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrhaenys <rrhaenys@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 13:12:03 by rrhaenys          #+#    #+#             */
/*   Updated: 2018/12/24 04:40:58 by rrhaenys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

# define WIN_W 1024
# define WIN_H 1024
# define WIN_W2 (WIN_W / 2)
# define WIN_H2 (WIN_H / 2)
# define WIN_S (WIN_W * WIN_H)
# define PRIN_RET(a,s) {if (a){ft_putendl(s); return (0);}}
# define X_P 0
# define Y_P 1

typedef struct	s_display
{
	int			local_x;
	int			local_y;
	float		scale;
	float		global_x;
	float		global_y;
	int			type;
	int			max_iter;
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
	void			*mlx_ptr;
	void			*mlx_win;
	t_img			img;
	t_display		*display;
}				t_data;

typedef struct	s_vertex
{
	float		p[2];
}				t_vertex;

int				key_release(int key, t_data *data);
int				mouse_move(int x, int y, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				ft_close(t_data *data);
void			ft_draw_px(t_data *env, int x, int y, int color);
void			clearwin(t_data *data);
int				draw(t_data *data);
void			test_draw(t_data *data);
void			ft_draw_mandelbrot(t_data *data);
void			ft_calc_mandelbrot(double range,
				double *min, int nmax, int *pres);
int				ft_get_color_mandelbrot(int n, int nmax);
void			ft_draw_julia(t_data *data);
int				*ft_calc_julia(t_data *data, float *r, float *d, float dw);
int				ft_get_color_julia(int value, int max, float *p, double r);

#endif
