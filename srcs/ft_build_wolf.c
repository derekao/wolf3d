/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_wolf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:17:09 by semartin          #+#    #+#             */
/*   Updated: 2016/04/26 14:17:54 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	under_water : Deal with the water lvl and the texture.
**					--> Water lvl depend on difficulty and time spent
**	---------------------------------------------------------------------------
**	get_texture_init : Init the texture t_fcoord
**						--> It depends on t_hit (On how the ray hit the wall)
**	---------------------------------------------------------------------------
**	build_wolf	: Core fnction of the game
**					--> Call the raycasting to get the distance
**					--> Deal with the wall, ground and roof
**					--> Deal with texture and watter
*/

static void		under_water(t_env *e, t_coord pixel, t_hit hit, t_fcoord *img2)
{
	t_fcoord	img3;

	img3.x = img2->x * (double)e->spiral->width / (double)e->texture->width;
	if ((int)hit.pos.x == 1 && (int)hit.pos.y == 18 && hit.pos.x - 1.0 == 0)
	{
		img3.y = img2->y * (double)e->spiral->height
					/ (double)e->texture->height;
		if (img2->y <= (double)e->texture->height
			* (1.0 - (e->opt.actual_time - e->opt.start_time)
			/ (double)e->opt.difficulty))
			ft_pixel_to_pixel(e->img, pixel, e->spiral, img3);
		else
			ft_water_to_pixel(e->img, pixel, e->spiral, img3);
		img2->y += ((double)e->texture->height / (double)hit.wall);
	}
	else
	{
		if (img2->y <= (double)e->texture->height
			* (1.0 - (e->opt.actual_time - e->opt.start_time)
			/ (double)e->opt.difficulty))
			ft_pixel_to_pixel(e->img, pixel, e->texture, *img2);
		else
			ft_water_to_pixel(e->img, pixel, e->texture, *img2);
		img2->y += ((double)e->texture->height / hit.wall);
	}
}

static void		get_texture_init(t_env *e, t_fcoord *pos, t_hit hit)
{
	double	tmp;

	if (modf(hit.pos.x, &tmp) != 0)
		pos->x = modf(hit.pos.x, &tmp) * (double)e->texture->width;
	else
		pos->x = modf(hit.pos.y, &tmp) * (double)e->texture->width;
	if ((HEIGHT - (int)hit.wall) < 0)
		pos->y = (double)e->texture->height *
					(hit.wall - HEIGHT) / 2.0 / hit.wall;
	else
		pos->y = 0;
}

void			ft_build_wolf(t_env *e)
{
	double		alpha;
	t_hit		hit;
	t_coord		pixel;
	t_fcoord	img2;

	pixel.x = 0;
	img2.x = 0;
	ft_game_over(e);
	while (pixel.x < WIDTH && e->opt.menu == 1)
	{
		pixel.y = -1;
		alpha = (double)pixel.x * MAX_ANGLE / (double)WIDTH + e->player.teta;
		get_dist(alpha, e, &hit, pixel);
		get_texture_init(e, &img2, hit);
		while (++pixel.y < HEIGHT)
		{
			if (pixel.y < (HEIGHT - (int)hit.wall) / 2)
				ft_pixel_put_image(e, e->img, pixel, 0x302010);
			else if (pixel.y < (int)hit.wall + (HEIGHT - (int)hit.wall) / 2)
				under_water(e, pixel, hit, &img2);
			else
				ft_pixel_put_image(e, e->img, pixel, 0x6666FF);
		}
		pixel.x++;
	}
}
