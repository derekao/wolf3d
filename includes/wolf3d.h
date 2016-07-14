/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:52:08 by semartin          #+#    #+#             */
/*   Updated: 2016/04/26 13:52:09 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "libft.h"

typedef struct		s_fcoord
{
	double			x;
	double			y;
}					t_fcoord;

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_hit
{
	double			dist;
	double			wall;
	t_fcoord		pos;
}					t_hit;

typedef struct		s_player
{
	t_fcoord		pos;
	double			teta;
}					t_player;

typedef struct		s_map
{
	int				width;
	int				height;
	int				**tab;
}					t_map;

typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	int				height;
	int				width;
}					t_img;

typedef struct		s_option
{
	long			start_time;
	long			actual_time;
	int				menu;
	int				difficulty;
	double			speed;

}					t_option;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	t_img			*img;
	t_img			*texture;
	t_img			*spiral;
	t_img			*victory;
	t_img			*over;
	t_img			*menu;
	t_player		player;
	t_map			map;
	t_option		opt;
}					t_env;

typedef struct		s_move
{
	int				up;
	int				down;
	int				right;
	int				left;
}					t_move;

# define ESCAP		53
# define UP			13
# define DOWN		1
# define LEFT		0
# define RIGHT		2
# define CAM_LEFT	123
# define CAM_RIGHT	124

# define ROTATION 	M_PI / 16.0
# define SPEED 		0.6

# define WIDTH		800
# define HEIGHT		800
# define MAX_ANGLE	M_PI / 3.0

/*
**					In ft_pixel_put_image
*/

void				ft_pixel_put_image(t_env *e, t_img *img, t_coord a,
										int color);
void				ft_pixel_to_pixel(t_img *img1, t_coord a, t_img *img2,
										t_fcoord b);
void				ft_water_to_pixel(t_img *img1, t_coord a, t_img *img2,
										t_fcoord b);

/*
**					In ft_math_wolf.c
*/

double				ft_modulo_reel(double x, double mod);
double				ft_offsetx_pos(t_env *e, double alpha);
double				ft_offsety_pos(t_env *e, double alpha);

/*
**					In ft_wall.c
*/

void				ft_texture(t_env *e);
void				ft_spiral(t_env *e);
void				ft_victory(t_env *e);
void				ft_over(t_env *e);
void				ft_menu(t_env *e);

/*
**					In ft_build_wold.c
*/

void				ft_build_wolf(t_env *e);

/*
**					In ft_map.c
*/

int					**ft_map(void);

/*
**					In the_key_event.c
*/

int					key_hook(int keycode, t_env *e);

/*
**					In ft_error.c
*/

void				ft_error(char const *str);
int					red_cross(t_env *e);

/*
**					In ft_raycasting.c
*/

void				get_dist(double alpha, t_env *e, t_hit *hit,
								t_coord pixel);

/*
**					In ft_menu.c
*/

void				ft_menu_win(t_env *e);
void				ft_game_over(t_env *e);
void				ft_get_difficulty(t_env *e);

#endif
