/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 23:55:08 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    hori_check(t_map *map, t_player *player, t_rays *rays)
{
	if (rays->ra > 0 && rays->ra < M_PI)
	{
		rays->ry = ((int)(player->pos_y / map->size) * map->size) - 0.0001;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = -map->size;
		rays->xo = -rays->yo * rays->atan;
		printf("DOWN ry: %d, rx: %d\n", (int)rays->ry, (int)rays->rx);
	}
	else if (rays->ra > M_PI)
	{
		rays->ry = ((int)(player->pos_y / map->size) * map->size) + map->size;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = map->size;
		rays->xo = -rays->yo * rays->atan;
		printf("UP ry: %d, rx: %d\n", (int)rays->ry, (int)rays->rx);
	}
	else
	{
		rays->rx = player->pos_x;
		rays->ry = player->pos_y;
		rays->dof = map->x;
		printf("SIDE ry: %d, rx: %d\n", (int)rays->ry, (int)rays->rx);
	}
}

void    hori_loop(t_map *map, t_player *player, t_rays *rays)
{
	rays->r = -1;
	rays->ra = player->angle;
	while (++rays->r < 1)
	{
		rays->dof = 0;
		rays->atan = -1 / tan(rays->ra);
		hori_check(map, player, rays);
		while (rays->dof < map->x)
		{
			if (rays->rx >= 0 && rays->rx < map->x
			    && rays->ry >= 0 && rays->ry < map->y)
			{
				printf("HIT\n");
				rays->dof = map->x;
			}
			else
			{
				rays->rx += rays->xo;
				rays->ry += rays->yo;
				rays->dof += 1;
			}
		}
	}
}

void	init_ray(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	hori_check(map, player, rays);
	draw_player_ray(map, &screen->map, (t_line){
		player->pos_xm, player->pos_ym,
		player->delta_x, player->delta_y,
		rays->rx, rays->ry,
		0, 0,
		rays->dist, chartohex("243, 156, 17", 0)});
}