/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put_to_image.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <semartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 12:50:34 by semartin          #+#    #+#             */
/*   Updated: 2015/09/17 13:18:04 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	ft_pixel_put_image : Put a pixel of the color on the image
** 	---------------------------------------------------------------------------
**	ft_pixel_to_pixel : Put a pixel from an image on an other one
** 	---------------------------------------------------------------------------
**	ft_water_to_pixel : Add blue to the image dest, feel like under water
*/

void	ft_pixel_put_image(t_env *e, t_img *img, t_coord a, int color)
{
	unsigned int pos;
	unsigned int mem;

	if (a.x >= 0 && a.x < WIDTH && a.y >= 0 && a.y < HEIGHT)
	{
		pos = (a.y * img->size_line) + ((img->bpp / 8) * a.x);
		mem = mlx_get_color_value(e->mlx, color);
		img->data[pos + 0] = (mem & 0xFF);
		img->data[pos + 1] = (mem & 0xFF00) >> 8;
		img->data[pos + 2] = (mem & 0xFF0000) >> 16;
	}
}

void	ft_pixel_to_pixel(t_img *img1, t_coord a, t_img *img2, t_fcoord b)
{
	unsigned int pos1;
	unsigned int pos2;

	if (b.x < img2->width && b.y < img2->height)
	{
		pos1 = (a.y * img1->size_line) + ((img1->bpp / 8) * a.x);
		pos2 = ((int)b.y * img2->size_line) + ((img2->bpp / 8) * (int)b.x);
		img1->data[pos1 + 0] = img2->data[pos2 + 0];
		img1->data[pos1 + 1] = img2->data[pos2 + 1];
		img1->data[pos1 + 2] = img2->data[pos2 + 2];
	}
}

void	ft_water_to_pixel(t_img *img1, t_coord a, t_img *img2, t_fcoord b)
{
	unsigned int pos1;
	unsigned int pos2;

	if (b.x < img2->width && b.y < img2->height)
	{
		pos1 = (a.y * img1->size_line) + ((img1->bpp / 8) * a.x);
		pos2 = ((int)b.y * img2->size_line) + ((img2->bpp / 8) * (int)b.x);
		img1->data[pos1 + 0] = img2->data[pos2 + 0] + 100;
		img1->data[pos1 + 1] = img2->data[pos2 + 1];
		img1->data[pos1 + 2] = img2->data[pos2 + 2];
	}
}
