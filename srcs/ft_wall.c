/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/10 17:33:04 by semartin          #+#    #+#             */
/*   Updated: 2016/07/10 17:33:04 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Everyfonction here allocate an image and store it inside the t_env :
** 		-> ft_texture : Wall Texture
**		-> ft_spiral : The portal at the end
**		-> ft_victory : Victory screen
**		-> ft_over : Game over screen
**		-> ft_menu : Difficulty menu
*/

#include "wolf3d.h"
#include <errno.h>

void	ft_texture(t_env *e)
{
	if (!(e->texture = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on ft_wall");
	e->texture->endian = 1;
	e->texture->ptr = mlx_xpm_file_to_image(e->mlx, "img/wall.xpm",
						&e->texture->width, &e->texture->height);
	e->texture->data = mlx_get_data_addr(e->texture->ptr, &(e->texture->bpp),
						&(e->texture->size_line), &(e->texture->endian));
}

void	ft_spiral(t_env *e)
{
	if (!(e->spiral = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on ft_wall");
	e->spiral->endian = 1;
	e->spiral->ptr = mlx_xpm_file_to_image(e->mlx, "img/spiral.xpm",
						&e->spiral->width, &e->spiral->height);
	e->spiral->data = mlx_get_data_addr(e->spiral->ptr, &(e->spiral->bpp),
						&(e->spiral->size_line), &(e->spiral->endian));
}

void	ft_victory(t_env *e)
{
	if (!(e->victory = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on ft_wall");
	e->victory->endian = 1;
	e->victory->ptr = mlx_xpm_file_to_image(e->mlx, "img/fireworks.xpm",
						&e->victory->width, &e->victory->height);
	e->victory->data = mlx_get_data_addr(e->victory->ptr, &(e->victory->bpp),
						&(e->victory->size_line), &(e->victory->endian));
}

void	ft_over(t_env *e)
{
	if (!(e->over = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on ft_wall");
	e->over->endian = 1;
	e->over->ptr = mlx_xpm_file_to_image(e->mlx, "img/gameover.xpm",
						&e->over->width, &e->over->height);
	e->over->data = mlx_get_data_addr(e->over->ptr, &(e->over->bpp),
						&(e->over->size_line), &(e->over->endian));
}

void	ft_menu(t_env *e)
{
	if (!(e->menu = malloc(sizeof(t_img))))
		ft_error("Abort : Allocation error on ft_wall");
	e->menu->endian = 1;
	e->menu->ptr = mlx_xpm_file_to_image(e->mlx, "img/menu.xpm",
						&e->menu->width, &e->menu->height);
	e->menu->data = mlx_get_data_addr(e->menu->ptr, &(e->menu->bpp),
						&(e->menu->size_line), &(e->menu->endian));
}
