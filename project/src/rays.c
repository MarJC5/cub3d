/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/06 11:09:42 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	rays_fov(t_game *game, t_player *player, t_rays *ray)
{
	int	r;

	r = 0;
	ray->angle = player->angle - DR * 30;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle > 2 * M_PI)
		ray->angle -= 2 * M_PI;
	while (r < 60)
	{
		ray->dist = 0;
		ray->deltax = cos(ray->angle) * (SPEED / 2);
		ray->deltay = sin(ray->angle) * (SPEED / 2);
		ray->dist = draw_ray(game->map, &game->screen.map, (t_line){
				player->pos_xm, player->pos_ym,
				ray->deltax, ray->deltay,
				ray->dist, 0x2e86de});
		//printf("ray dist %d: %f\n", r, ray->dist);
		ray->angle += DR;
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		r++;
	}
}
