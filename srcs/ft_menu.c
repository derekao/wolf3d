/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 14:18:54 by semartin          #+#    #+#             */
/*   Updated: 2016/07/11 14:18:54 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	ft_menu_win : Print the win screen with "You Won" on it
**	---------------------------------------------------------------------------
**	ft_game_over : Print game over if you loose the game
**	---------------------------------------------------------------------------
**	mouse_hook : Get mouse movement (For the difficulty choice)
**	---------------------------------------------------------------------------
**	escape_hook : If Escape is pressed, leave the program
**	---------------------------------------------------------------------------
**	ft_get_difficulty : Call the mouse_hook if any mouse clic
*/

void			ft_menu_win(t_env *e)
{
	e->opt.menu = 2;
	mlx_destroy_image(e->mlx, e->img->ptr);
	e->img = e->victory;
	mlx_put_image_to_window(e->mlx, e->win, e->img->ptr, 0, 0);
	mlx_string_put(e->mlx, e->win, WIDTH / 2 - 24,
					HEIGHT / 2 - 16, 0xFF0000, "You Won !");
}

void			ft_game_over(t_env *e)
{
	if (e->opt.difficulty - (e->opt.actual_time - e->opt.start_time)
			<= -e->opt.difficulty / 3)
	{
		e->opt.menu = 2;
		mlx_destroy_image(e->mlx, e->img->ptr);
		e->img = e->over;
		mlx_put_image_to_window(e->mlx, e->win, e->img->ptr, 0, 0);
	}
}

static int		mouse_hook(int key, int x, int y, t_env *e)
{
	if (key == 1 && e->opt.menu == 0)
	{
		e->opt.menu = 1;
		e->opt.start_time = time(NULL);
		e->opt.actual_time = time(NULL);
		if (x >= 246 && x <= 567 && y >= 170 && y <= 211)
			e->opt.difficulty = 10000.0;
		else if (x >= 220 && x <= 593 && y >= 229 && y <= 270)
			e->opt.difficulty = 300.0;
		else if (x >= 149 && x <= 664 && y >= 289 && y <= 330)
			e->opt.difficulty = 180.0;
		else if (x >= 245 && x <= 560 && y >= 349 && y <= 389)
			e->opt.difficulty = 60.0;
		else if (x >= 219 && x <= 593 && y >= 406 && y <= 445)
			e->opt.difficulty = 30.0;
		else
		{
			e->opt.menu = 0;
			return (0);
		}
		ft_build_wolf(e);
		mlx_put_image_to_window(e->mlx, e->win, e->img->ptr, 0, 0);
		mlx_key_hook(e->win, key_hook, e);
	}
	return (0);
}

static int		escape_hook(int key, t_env *e)
{
	if (key == ESCAP && e)
		exit(0);
	return (0);
}

void			ft_get_difficulty(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->menu->ptr, 0, 0);
	mlx_key_hook(e->win, escape_hook, e);
	mlx_mouse_hook(e->win, mouse_hook, e);
	mlx_hook(e->win, 17, (1L << 17), red_cross, e);
}
