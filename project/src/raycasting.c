/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/15 11:11:00 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_orientation(t_game *game, t_rays *ray)
{
	(void)game;
	if (ray->door == 1)
	{
		ray->color = YELLOW;
		ray->door = 0;
		return (0);
	}
	if (ray->ra < degtorad(180))
	{
		if (ray->ra > degtorad(90)
		&& ray->ra < degtorad(270))
			ray->color = GREY;
		else if (ray->ra < degtorad(90)
		|| ray->ra > degtorad(270))
			ray->color = GREY;
	}
	else if (ray->ra > degtorad(180))
	{
		if (ray->ra > degtorad(90)
		&& ray->ra < degtorad(270))
			ray->color = GREEN;
		else if (ray->ra < degtorad(90)
		|| ray->ra > degtorad(270))
			ray->color = GREEN;
	}
	return (radtodeg(ray->ra));
}

int	init_orientation_v(t_game *game, t_rays *ray)
{
	(void)game;
	if (ray->door == 1)
	{
		ray->color = YELLOW;
		ray->door = 0;
		return (0);
	}
	if (ray->ra < degtorad(180))
	{
		if (ray->ra > degtorad(90)
		&& ray->ra < degtorad(270))
			ray->color = BLUE;
		else if (ray->ra < degtorad(90)
		|| ray->ra > degtorad(270))
			ray->color = BLACK;
	}
	else if (ray->ra > degtorad(180))
	{
		if (ray->ra > degtorad(90)
		&& ray->ra < degtorad(270))
			ray->color = BLUE;
		else if (ray->ra < degtorad(90)
		|| ray->ra > degtorad(270))
			ray->color = BLACK;
	}
	return (radtodeg(ray->ra));
}
