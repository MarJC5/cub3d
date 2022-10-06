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

void	verti_check(t_map *map, t_player *player, t_rays *rays)
{
	rays->vshift = 0;
	if (rays->ra > degtorad(90) && rays->ra < degtorad(270))
	{
		rays->rx = ((int)(player->pos_xm / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->ry = (player->pos_xm - rays->rx) * rays->ntan + player->pos_ym;
		rays->xo = -MINI_TILE;
		rays->vshift = -1;
		rays->yo = -rays->xo * rays->ntan;
	}
	else if ((rays->ra < degtorad(90) || rays->ra > degtorad(270)))
	{
		rays->rx = ((int)(player->pos_xm / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->ry = (player->pos_xm - rays->rx) * rays->ntan + player->pos_ym;
		rays->xo = MINI_TILE;
		rays->vshift = -1;
		rays->yo = -rays->xo * rays->ntan;
	}
	else
	{
		rays->rx = player->pos_xm;
		rays->ry = player->pos_ym;
		rays->dof = map->y;
	}
}

void	set_value_v(t_map *map, t_player *player, t_rays *rays)
{
	(void)map;
	rays->dof = 0;
	rays->vx = player->pos_xm;
	rays->vy = player->pos_ym;
	rays->dis_v = 1000000;
	rays->ntan = -tan(rays->ra);
}

void	door_v(t_map *map, t_rays *rays)
{
	if (map->scene[(int)rays->vmry][(int)rays->vmrx] == DOOR)
	{
		rays->doorv = 1;
		rays->dis_v += 0;
	}
}

void	verti_loop( t_map *map, t_player *player, t_rays *rays)
{
	set_value_v(map, player, rays);
	verti_check(map, player, rays);
	while (rays->dof < map->y + map->size)
	{
		rays->vmrx = ((int)rays->rx / MINI_TILE) + rays->vshift;
		rays->vmry = ((int)rays->ry / MINI_TILE) + rays->vshift;
		if (rays->vmrx >= 0 && rays->vmrx < map->x
			&& rays->vmry >= 0 && rays->vmry < map->y
			&& (map->scene[(int)rays->vmry][(int)rays->vmrx] == '1'
			|| map->scene[(int)rays->vmry][(int)rays->vmrx] == DOOR))
		{
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->dis_v = dist(player, rays);
			door_v(map, rays);
			rays->dof = map->y;
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
