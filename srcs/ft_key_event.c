/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 14:14:21 by semartin          #+#    #+#             */
/*   Updated: 2016/04/28 14:14:23 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	usefull_key : Check if the keypresed is suppose to do smthg or not
**	---------------------------------------------------------------------------
**	not_trow_wall : Block the player to get trow any wall
**	---------------------------------------------------------------------------
**	change_player_pos : Change the play position, use the camera angle
**	---------------------------------------------------------------------------
**	player_pos : Deal with key_event that change player pos or camera angle
**	---------------------------------------------------------------------------
**	key_hook : Hook key pressed, exit if escap is pressed
**				Call play_pos if the key pressed is usefull
*/

static int	usefull_key(int keycode)
{
	if (keycode == UP
		|| keycode == DOWN
		|| keycode == LEFT
		|| keycode == RIGHT
		|| keycode == CAM_LEFT
		|| keycode == CAM_RIGHT)
		return (1);
	else
		return (0);
}

static void	not_trow_wall(t_fcoord *true_pos, t_fcoord pos, t_map *map,
							t_env *e)
{
	if (pos.x < 0 || pos.x > 20 || pos.y < 0 || pos.y > 20)
		return ;
	if (map->tab[(int)pos.x][(int)pos.y] == 0)
	{
		true_pos->x = pos.x;
		true_pos->y = pos.y;
	}
	if ((int)true_pos->x == 1 && (int)true_pos->y == 18)
	{
		e->opt.menu = 0;
		ft_menu_win(e);
	}
}

static void	change_player_pos(t_player *p, t_move *move, t_map *map,
								t_env *e)
{
	t_fcoord		pos;

	if (move->up == 1)
	{
		pos.x = p->pos.x - cos(p->teta + M_PI * 4.0 / 6.0) * e->opt.speed;
		pos.y = p->pos.y + sin(p->teta + M_PI * 4.0 / 6.0) * e->opt.speed;
	}
	else if (move->left == 1)
	{
		pos.x = p->pos.x + cos(p->teta + M_PI * 7.0 / 6.0) * e->opt.speed;
		pos.y = p->pos.y - sin(p->teta + M_PI * 7.0 / 6.0) * e->opt.speed;
	}
	else if (move->down == 1)
	{
		pos.x = p->pos.x - cos(p->teta + M_PI * 10.0 / 6.0) * e->opt.speed;
		pos.y = p->pos.y + sin(p->teta + M_PI * 10.0 / 6.0) * e->opt.speed;
	}
	else
	{
		pos.x = p->pos.x + cos(p->teta + M_PI * 1.0 / 6.0) * e->opt.speed;
		pos.y = p->pos.y - sin(p->teta + M_PI * 1.0 / 6.0) * e->opt.speed;
	}
	not_trow_wall(&p->pos, pos, map, e);
}

static void	player_pos(int keycode, t_env *e)
{
	t_move	move;

	move.up = 0;
	move.down = 0;
	move.right = 0;
	move.left = 0;
	if (keycode == UP)
		move.up = 1;
	else if (keycode == DOWN)
		move.down = 1;
	else if (keycode == LEFT)
		move.left = 1;
	else if (keycode == RIGHT)
		move.right = 1;
	else if (keycode == CAM_LEFT)
		e->player.teta -= ROTATION;
	else if (keycode == CAM_RIGHT)
		e->player.teta += ROTATION;
	if (move.up || move.down || move.right || move.left)
		change_player_pos(&e->player, &move, &e->map, e);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == ESCAP)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	if (e->opt.menu == 0 || e->opt.menu == 2)
		return (0);
	if (!e)
		exit(0);
	else
		player_pos(keycode, e);
	if (usefull_key(keycode))
	{
		e->opt.actual_time = time(NULL);
		e->opt.speed = SPEED * (1.0 - (e->opt.actual_time - e->opt.start_time)
						/ (double)e->opt.difficulty);
		if (e->opt.speed < 0.3 * SPEED)
			e->opt.speed = 0.3 * SPEED;
		ft_build_wolf(e);
		if (e->opt.menu == 1)
			mlx_put_image_to_window(e->mlx, e->win, e->img->ptr, 0, 0);
	}
	return (0);
}
