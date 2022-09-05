/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/05 18:59:43 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	h_loop(t_map *map, t_player *player, t_rays *rays)
{
	(void) player;
	rays->dis_h = 1000000;
	while (rays->dof < map->x)
	{
		rays->hmy = ((int)rays->ry) / MINI_TILE;
		rays->hmx = ((int)rays->rx) / MINI_TILE;
		printf("hmy: %d, hmx: %d\n\n", rays->hmy, rays->hmx);
		if (rays->hmx >= 0 && rays->hmx < map->x && rays->hmy >= 0
			&& rays->hmy < map->y
			&& map->scene[rays->hmy][rays->hmx] == '1')
		{
			rays->hy = rays->ry;
			rays->hx = rays->rx;
			rays->dof = map->x;
		}
		else
		{
			rays->ry += rays->yo;
			rays->rx += rays->xo;
			rays->dof += 1;
		}
	}
}

void	v_loop(t_map *map, t_player *player, t_rays *rays)
{
	(void) player;
	rays->dis_v = 1000000;
	while (rays->dof < map->y - 2)
	{
		rays->vmy = ((int)rays->ry) / MINI_TILE;
		rays->vmx = ((int)rays->rx) / MINI_TILE;
		if (rays->rx >= 0 && rays->rx < map->x && rays->ry >= 0
			&& rays->ry < map->y
			&& map->scene[rays->vmy][rays->vmx] == '1')
		{
			rays->vy = rays->ry;
			rays->vx = rays->rx;
			rays->dof = map->y;
		}
		else
		{
			rays->ry += rays->yo;
			rays->rx += rays->xo;
			rays->dof += 1;
		}
	}
}

void	h_check(t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->h_shift = 0;
	rays->atan = -1 / tan(rays->ra);
	if (rays->ra > 0 && rays->ra < degtorad(180))
	{
		rays->ry = (((int)player->pos_y / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = -MINI_TILE;
		rays->xo = -rays->yo * rays->atan;
		rays->h_shift = -1;
	}
	else if (rays->ra > degtorad(180))
	{
		rays->ry = (((int)player->pos_y / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
		rays->yo = MINI_TILE;
		rays->xo = -rays->yo * rays->atan;
	}
	else
	{
		rays->ry = player->pos_y;
		rays->rx = player->pos_x;
		rays->dof = map->x;
	}
	h_loop(map, player, rays);
}

void	v_check(t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->v_shift = 0;
	rays->ntan = -tan(rays->ra);
	if (rays->ra > degtorad(90) && rays->ra < degtorad(270))
	{
		rays->rx = (((int)player->pos_x / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->ry = (player->pos_x - rays->rx) * rays->ntan + player->pos_y;
		rays->xo = -MINI_TILE;
		rays->yo = -rays->xo * rays->ntan;
		rays->v_shift = -1;
	}
	else if (rays->ra < degtorad(90) || rays->ra > degtorad(270))
	{
		rays->rx = (((int)player->pos_x / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->ry = (player->pos_x - rays->rx) * rays->ntan + player->pos_y;
		rays->xo = MINI_TILE;
		rays->yo = -rays->xo * rays->ntan;
	}
	else
	{
		rays->ry = player->pos_y;
		rays->rx = player->pos_x;
		rays->dof = map->y;
	}
	v_loop(map, player, rays);
}

void	init_ray(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	rays->dist = 0;
	rays->r = 0;
	rays->ra = player->angle;
	while (rays->r++ < 1)
	{
		h_check(map, player, rays);
		v_check(map, player, rays);
		draw_line(&screen->map, (t_dline){
			player->pos_xm, player->pos_ym,
			rays->hx, rays->hy, rays->dis_h,
			0x00b894});
		draw_line(&screen->map, (t_dline){
			player->pos_xm, player->pos_ym,
			rays->vx, rays->vy, rays->dis_v,
			0xcccccc});
	}
}
