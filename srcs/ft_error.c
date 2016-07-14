/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 14:07:07 by semartin          #+#    #+#             */
/*   Updated: 2016/07/09 14:07:11 by semartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	ft_error : Exit and print and error message if any crash occures
**	---------------------------------------------------------------------------
**	red_cross : Exit the program proprely if red_cross is pressed
*/

void	ft_error(char const *str)
{
	ft_putendl_fd(str, 2);
	exit(0);
}

int		red_cross(t_env *e)
{
	if (e)
	{
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
	}
	return (0);
}
