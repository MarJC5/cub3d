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
		printf("Looking DOWN\n");
		rays->ry = ((int)(player->pos_y / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = -MINI_TILE;
		rays->xo = -rays->yo * rays->atan;
	}
	else if (rays->ra > M_PI)
	{
		printf("Looking UP\n");
		rays->ry = ((int)(player->pos_y / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = MINI_TILE;
		rays->xo = -rays->yo * rays->atan;
	}
	else
	{
		printf("Looking LEFT - RIGHT\n");
		rays->rx = player->pos_x;
		rays->ry = player->pos_y;
		rays->dof = map->x;
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
			rays->mx = ((int)rays->rx) / MINI_TILE;
			rays->my = ((int)rays->ry) / MINI_TILE;
			if (rays->rx >= 0 && rays->rx < map->x
				&& rays->ry >= 0 && rays->ry < map->y
				&& map->scene[(int)rays->my][(int)rays->mx] == '1')
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
	hori_loop(map, player, rays);
	printf("posmx: %d posmy: %d\nposx: %d posy: %d\n",
	       (int)rays->mx, (int)rays->my,
	       (int)player->pos_x,  (int)player->pos_y);
	draw_ray(&screen->map, (t_line){
		player->pos_xm,
		player->pos_ym,
		player->pos_xm + player->delta_x * MINI_TILE,
		player->pos_ym + player->delta_y * MINI_TILE,
		player->delta_x, player->delta_y,
		chartohex("243, 156, 17", 0)});
}