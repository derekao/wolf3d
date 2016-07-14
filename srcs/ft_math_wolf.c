/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_wolf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 15:08:08 by semartin          #+#    #+#             */
/*   Updated: 2016/07/09 15:08:08 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	ft_modulo_reel : Get the modulo of a float_part
**	---------------------------------------------------------------------------
**	ft_offsetX_pos : Get the offset to find the player pos.x
**	---------------------------------------------------------------------------
**	ft_offsetY_pos : Get the offset to find the player pos.y
*/

double		ft_modulo_reel(double x, double mod)
{
	if (x < 0)
	{
		while (x < 0)
			x += mod;
	}
	else
	{
		while (x >= mod)
			x -= mod;
	}
	return (x);
}

double		ft_offsetx_pos(t_env *e, double alpha)
{
	double tmp;
	double float_part;

	float_part = modf(e->player.pos.x, &tmp);
	if (sin(alpha) > 0.0)
		float_part = 1.0 - float_part;
	return (float_part);
}

double		ft_offsety_pos(t_env *e, double alpha)
{
	double tmp;
	double float_part;

	float_part = modf(e->player.pos.y, &tmp);
	if (cos(alpha) > 0.0)
		float_part = 1.0 - float_part;
	return (float_part);
}
