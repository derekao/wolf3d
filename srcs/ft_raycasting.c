/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 17:32:30 by semartin          #+#    #+#             */
/*   Updated: 2016/07/12 17:32:31 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	wall_3d : Find if the ray hit a wall or not
**				--> Map is a tab of int while wall is suppose to be a square.
**	---------------------------------------------------------------------------
**	get_upray_dist : Get the dist between the player and the first hit with Y
**	---------------------------------------------------------------------------
**	get_rightray_dist : Get the dist between the player and the 1st hit with X
**	---------------------------------------------------------------------------
**	get_dist : Get the shortes dist between both.
**				--> It's the real dist between the player and the wall
**				--> Get the "hit" to know where the ray came from
*/

static int		wall_3d(t_fcoord inter, t_fcoord pos, t_env *e)
{
	if (inter.x >= 0 && inter.y >= 0
		&& e->map.tab[(int)(pos.x + 0.0001)][(int)(pos.y + 0.0001)])
		return (0);
	else if (inter.x >= 0 && inter.y <= 0 && pos.y != 0)
	{
		if (e->map.tab[(int)(pos.x + 0.0001)][(int)(pos.y - 0.0001)])
			return (0);
	}
	else if (inter.x <= 0 && inter.y >= 0 && pos.x != 0)
	{
		if (e->map.tab[(int)(pos.x - 0.0001)][(int)(pos.y + 0.0001)])
			return (0);
	}
	else if (inter.x <= 0 && inter.y <= 0 && pos.y != 0 && pos.x != 0)
	{
		if (e->map.tab[(int)(pos.x - 0.0001)][(int)(pos.y - 0.0001)])
			return (0);
	}
	else
		return (1);
	return (1);
}

static void		get_upray_dist(double alpha, t_env *e, t_hit *hit)
{
	t_fcoord	inter;
	double		distx;
	double		disty;

	inter.y = (cos(alpha) > 0.0) ? 1 : -1;
	inter.x = inter.y * tan(alpha);
	hit->pos.y = e->player.pos.y + inter.y * ft_offsety_pos(e, alpha);
	hit->pos.x = e->player.pos.x + inter.x * ft_offsety_pos(e, alpha);
	while ((int)hit->pos.x >= 0 && (int)hit->pos.x < e->map.width
			&& (int)hit->pos.y >= 0 && (int)hit->pos.y < e->map.height)
	{
		if (!wall_3d(inter, hit->pos, e))
			break ;
		hit->pos.y += inter.y;
		hit->pos.x += inter.x;
	}
	distx = hit->pos.x - e->player.pos.x;
	disty = hit->pos.y - e->player.pos.y;
	hit->dist = sqrt((distx * distx) + (disty * disty));
}

static void		get_rightray_dist(double alpha, t_env *e, t_hit *hit)
{
	t_fcoord	inter;
	double		distx;
	double		disty;

	inter.x = (sin(alpha) > 0.0) ? 1 : -1;
	inter.y = (tan(alpha) != 0) ? inter.x / tan(alpha) : inter.x * 5000;
	hit->pos.y = e->player.pos.y + inter.y * ft_offsetx_pos(e, alpha);
	hit->pos.x = e->player.pos.x + inter.x * ft_offsetx_pos(e, alpha);
	while ((int)hit->pos.x >= 0 && (int)hit->pos.x < e->map.width
			&& (int)hit->pos.y >= 0 && (int)hit->pos.y < e->map.height)
	{
		if (!wall_3d(inter, hit->pos, e))
			break ;
		hit->pos.y += inter.y;
		hit->pos.x += inter.x;
	}
	distx = hit->pos.x - e->player.pos.x;
	disty = hit->pos.y - e->player.pos.y;
	hit->dist = sqrt((distx * distx) + (disty * disty));
}

void			get_dist(double alpha, t_env *e, t_hit *hit, t_coord pixel)
{
	t_hit		hitx;
	t_hit		hity;

	get_upray_dist(alpha, e, &hitx);
	get_rightray_dist(alpha, e, &hity);
	if (hitx.dist <= hity.dist)
	{
		hit->dist = hitx.dist * cos((double)pixel.x * MAX_ANGLE
						/ (double)WIDTH - M_PI / 6.0);
		hit->wall = (int)((double)WIDTH / 1.5 / hit->dist);
		hit->pos.x = hitx.pos.x;
		hit->pos.y = hitx.pos.y;
	}
	else
	{
		hit->dist = hity.dist * cos((double)pixel.x * MAX_ANGLE
						/ (double)WIDTH - M_PI / 6.0);
		hit->wall = (int)((double)WIDTH / 1.5 / hit->dist);
		hit->pos.x = hity.pos.x;
		hit->pos.y = hity.pos.y;
	}
}
