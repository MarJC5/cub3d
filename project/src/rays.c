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

void    rays_check(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	rays->r = -1;
	rays->ra = player->angle - DR * 30;
	if (rays->ra < 0)
		rays->ra += 2 * PI;
	if (rays->ra > 2 * PI)
		rays->ra -= 2 * PI;
	while (++rays->r < 1)
	{
		rays->dof = -1;
		rays->ntan = -tan(rays->ra);
		rays->dis_v = 1000000;
		rays->vy = player->pos_y;
		rays->vx = player->pos_x;
		if (rays->ra > degtorad(90) && rays->ra < degtorad(270))
		{
			rays->rx = (((int)player->pos_x / MINI_TILE) * MINI_TILE);
			rays->ry = (player->pos_x - rays->rx) * rays->ntan + player->pos_y;
			rays->xo = -MINI_TILE;
			rays->yo = -rays->xo * rays->ntan;
			printf("Looking LEFT\n");
		}
		else if (rays->ra < degtorad(90) || rays->ra > degtorad(270))
		{
			rays->rx = (((int)player->pos_x / MINI_TILE) * MINI_TILE) + MINI_TILE;
			rays->ry = (player->pos_x - rays->rx) * rays->ntan + player->pos_y;
			rays->xo = MINI_TILE;
			rays->yo = -rays->xo * rays->ntan;
			printf("Looking RIGHT\n");
		}
		else
		{
			rays->ry = player->pos_y;
			rays->rx = player->pos_x;
			rays->dof = map->x;
			printf("Looking UP - DOWN\n");
		}
		while (++rays->dof < map->y)
		{
			rays->vmy = ((int)rays->ry) / MINI_TILE;
			rays->vmx = ((int)rays->rx) / MINI_TILE;
			if (rays->rx > 0 && rays->rx < map->x
			    && rays->ry > 0 && rays->ry < map->y
			    && map->scene[(int)rays->vmy][(int)rays->vmx] == '1')
			{
				rays->vy = rays->ry;
				rays->vx = rays->rx;
				rays->dis_v = sqrt(powf((rays->rx - player->pos_x), 2)
				                   + powf((rays->ry - player->pos_y), 2));
				rays->dof = map->y;
			}
			else
			{
				rays->ry += rays->yo;
				rays->rx += rays->xo;
			}
		}

		rays->dof = -1;
		rays->atan = -1 / tan(rays->ra);
		rays->dis_h = 1000000;
		rays->hy = player->pos_y;
		rays->hx = player->pos_x;
		if (rays->ra > 0 && rays->ra < degtorad(180))
		{
			rays->ry = (((int)player->pos_y / MINI_TILE) * MINI_TILE);
			rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
			rays->yo = -MINI_TILE;
			rays->xo = -rays->yo * rays->atan;
			printf("Looking UP\n");
		}
		else if (rays->ra > degtorad(180))
		{
			rays->ry = (((int)player->pos_y / MINI_TILE) * MINI_TILE) + MINI_TILE;
			rays->rx = (player->pos_y - rays->ry) * rays->atan + player->pos_x;
			rays->yo = MINI_TILE;
			rays->xo = -rays->yo * rays->atan;
			printf("Looking DOWN\n");
		}
		else
		{
			rays->ry = player->pos_y;
			rays->rx = player->pos_x;
			rays->dof = map->x;
			printf("Looking LEFT - RIGHT\n");
		}
		while (++rays->dof < map->x)
		{
			rays->hmy = ((int)rays->ry) / MINI_TILE;
			rays->hmx = ((int)rays->rx) / MINI_TILE;
			if (rays->rx >= 0 && rays->rx < map->x
			    && rays->ry >= 0 && rays->ry < map->y
			    && map->scene[(int)rays->hmy][(int)rays->hmx] == '1')
			{
				rays->hy = rays->ry;
				rays->hx = rays->rx;
				rays->dis_h = sqrt(powf((rays->rx - player->pos_x), 2)
				                   + powf((rays->ry - player->pos_y), 2));
				rays->dof = map->x;
			}
			else
			{
				rays->ry += rays->yo;
				rays->rx += rays->xo;
			}
		}
		if (rays->dis_v < rays->dis_h)
		{
			rays->ry = rays->vy;
			rays->rx = rays->vx;
			printf("DIST: %lf\n", rays->dis_v);
		}
		if (rays->dis_h < rays->dis_v)
		{
			rays->ry = rays->hy;
			rays->rx = rays->hx;
			printf("DIST: %lf\n", rays->dis_h);
		}
		draw_line(&screen->map, (t_dline){
		player->pos_xm, player->pos_ym,
		rays->rx, rays->ry,
		rays->dist,
		chartohex("243, 156, 17", 0)});
//		rays->dist = draw_player_ray(map, &screen->map, (t_line){
//			player->pos_xm, player->pos_ym,
//			rays->rx, rays->ry,
//			rays->dist,
//			chartohex("243, 156, 17", 0)});
		rays->ra = rays->ra - 1;                                                              //go to next ray
	}
}

void	init_ray(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	rays->dist = 0;
	rays_check(map, screen, player, rays);
}
