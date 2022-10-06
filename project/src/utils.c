/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:04:35 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/19 07:49:46 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	degtorad(float ang)
{
	return (ang * M_PI / 180.0);
}

float	radtodeg(float ang)
{
	return (ang * (180.0 / M_PI));
}

int	fixang(int ang)
{
	if (ang > 359)
		ang -= 360;
	if (ang < 0)
		ang += 360;
	return (ang);
}

void	reset_angle(t_rays *ray)
{
	ray->doorh = 0;
	ray->door = 0;
	ray->doorv = 0;
	if (ray->ra > 2 * M_PI)
		ray->ra -= 2 * M_PI;
	if (ray->ra < 0)
		ray->ra += 2 * M_PI;
}

float	dist(t_player *player, t_rays *rays)
{
	return (sqrt(powf((rays->rx - player->pos_xm), 2)
			+ powf((rays->ry - player->pos_ym), 2)));
}
