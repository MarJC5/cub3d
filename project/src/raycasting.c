/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 12:25:41 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_orientation(t_game *game, t_rays *ray)
{
	if (ray->ra < degtorad(180))
	{
		if (ray->ra > degtorad(90)
			&& ray->ra < degtorad(270))
			ray->text = game->text.no;
		else if (ray->ra < degtorad(90)
			|| ray->ra > degtorad(270))
			ray->text = game->text.no;
	}
	else if (ray->ra > degtorad(180))
	{
		if (ray->ra > degtorad(90)
			&& ray->ra < degtorad(270))
			ray->text = game->text.so;
		else if (ray->ra < degtorad(90)
			|| ray->ra > degtorad(270))
			ray->text = game->text.so;
	}
	return (radtodeg(ray->ra));
}

int	init_orientation_v(t_game *game, t_rays *ray)
{
	if (ray->ra < degtorad(180))
	{
		if (ray->ra > degtorad(90)
			&& ray->ra < degtorad(270))
			ray->text = game->text.ea;
		else if (ray->ra < degtorad(90)
			|| ray->ra > degtorad(270))
			ray->text = game->text.we;
	}
	else if (ray->ra > degtorad(180))
	{
		if (ray->ra > degtorad(90)
			&& ray->ra < degtorad(270))
			ray->text = game->text.ea;
		else if (ray->ra < degtorad(90)
			|| ray->ra > degtorad(270))
			ray->text = game->text.we;
	}
	return (radtodeg(ray->ra));
}
