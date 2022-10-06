/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/19 08:01:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	hori_check(t_map *map, t_player *player, t_rays *rays)
{
	rays->hshift = 0;
	if (rays->ra > degtorad(180))
	{
		rays->ry = ((int)(player->pos_ym / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->rx = (player->pos_ym - rays->ry) * rays->atan + player->pos_xm;
		rays->yo = -MINI_TILE;
		rays->hshift = -1;
		rays->xo = -rays->yo * rays->atan;
	}
	else if (rays->ra < degtorad(180))
	{
		rays->ry = ((int)(player->pos_ym / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->rx = (player->pos_ym - rays->ry) * rays->atan + player->pos_xm;
		rays->yo = MINI_TILE;
		rays->hshift = -1;
		rays->xo = -rays->yo * rays->atan;
	}
	else
	{
		rays->rx = player->pos_xm;
		rays->ry = player->pos_ym;
		rays->dof = map->x;
	}
}

void	set_value_h(t_map *map, t_player *player, t_rays *rays)
{
	(void)map;
	rays->dof = 0;
	rays->hx = player->pos_xm;
	rays->hy = player->pos_ym;
	rays->dis_h = 1000000;
	rays->atan = -1 / tan(rays->ra);
}

void	door_h(t_map *map, t_rays *rays)
{
	if (map->scene[(int)rays->hmry][(int)rays->hmrx] == DOOR)
	{
		rays->doorh = 1;
		rays->dis_h += 0;
	}
}

void	hori_loop(t_map *map, t_player *player, t_rays *rays)
{
	set_value_h(map, player, rays);
	hori_check(map, player, rays);
	while (rays->dof < map->x + map->size)
	{
		rays->hmrx = ((int)rays->rx / MINI_TILE) + rays->hshift;
		rays->hmry = ((int)rays->ry / MINI_TILE) + rays->hshift;
		if (rays->hmrx >= 0 && rays->hmrx < map->x
			&& rays->hmry >= 0 && rays->hmry < map->y
			&& (map->scene[(int)rays->hmry][(int)rays->hmrx] == '1'
			|| map->scene[(int)rays->hmry][(int)rays->hmrx] == DOOR))
		{
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->dis_h = dist(player, rays);
			door_h(map, rays);
			rays->dof = map->x;
			break ;
		}
		else
		{
			rays->rx += rays->xo;
			rays->ry += rays->yo;
			rays->dof += 1;
		}
	}
}
