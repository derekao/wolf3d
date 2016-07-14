/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 13:51:34 by semartin          #+#    #+#             */
/*   Updated: 2016/04/26 13:51:38 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	init_evn : Initilise the t_env struc
** 	---------------------------------------------------------------------------
**	main : _MAIN_ call needed function
*/

#include "wolf3d.h"

static void	init_env(t_env *e)
{
	if (!(e->img = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on init_env");
	e->map.tab = ft_map();
	e->map.width = 20;
	e->map.height = 20;
	e->opt.menu = 0;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "Wolf3d");
	e->img->endian = 1;
	e->img->ptr = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->img->data = mlx_get_data_addr(e->img->ptr, &(e->img->bpp),
							&(e->img->size_line), &(e->img->endian));
	e->player.pos.x = 3.5;
	e->player.pos.y = 1.5;
	e->player.teta = -M_PI / 6.0 + M_PI / 2;
	e->opt.difficulty = 30.0;
	e->opt.speed = SPEED;
}

int			main(void)
{
	t_env	e;

	init_env(&e);
	ft_texture(&e);
	ft_spiral(&e);
	ft_victory(&e);
	ft_over(&e);
	ft_menu(&e);
	ft_get_difficulty(&e);
	if (e.opt.menu == 1)
	{
		ft_build_wolf(&e);
		mlx_key_hook(e.win, key_hook, &e);
	}
	mlx_hook(e.win, 17, (1L << 17), red_cross, &e);
	mlx_loop(e.mlx);
	mlx_destroy_image(e.mlx, e.img->ptr);
	mlx_destroy_image(e.mlx, e.texture->ptr);
	mlx_destroy_image(e.mlx, e.spiral->ptr);
	mlx_destroy_image(e.mlx, e.victory->ptr);
	mlx_destroy_image(e.mlx, e.over->ptr);
	mlx_destroy_window(e.mlx, e.win);
	return (0);
}
