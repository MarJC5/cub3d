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
	if (rays->ra > M_PI)
	{
		rays->ry = ((int)(player->pos_ym / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->rx = (player->pos_ym - rays->ry) * rays->atan + player->pos_xm;
		rays->yo = -MINI_TILE;
		rays->hshift = -1;
		rays->xo = -rays->yo * rays->atan;
	}
	else if (rays->ra < M_PI)
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

void	hori_loop(t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->hx = player->pos_xm;
	rays->hy = player->pos_ym;
	rays->dis_h = 1000000;
	rays->atan = -1 / tan(rays->ra);
	hori_check(map, player, rays);
	while (rays->dof < map->x - 2)
	{
		rays->hmrx = ((int)rays->rx / MINI_TILE) + rays->hshift;
		rays->hmry = ((int)rays->ry / MINI_TILE) + rays->hshift;
		if (rays->hmrx >= 0 && rays->hmrx < map->x
			&& rays->hmry >= 0 && rays->hmry < map->y
			&& map->scene[(int)rays->hmry]
			[(int)rays->hmrx] == '1')
		{
			printf("HY: %d, HX: %d\n", (int)rays->hmry, (int)rays->hmrx);
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->dis_h = dist(player, rays);
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

void	verti_check(t_map *map, t_player *player, t_rays *rays)
{
	rays->vshift = 0;
	if (rays->ra > M_PI / 2 && rays->ra < 3 * M_PI / 2)
	{
		rays->rx = ((int)(player->pos_xm / MINI_TILE) * MINI_TILE) - 0.0001;
		rays->ry = (player->pos_xm - rays->rx) * rays->ntan + player->pos_ym;
		rays->xo = -MINI_TILE;
		rays->vshift = -1;
		rays->yo = -rays->xo * rays->ntan;
	}
	else if (rays->ra < M_PI / 2 || rays->ra > 3 * M_PI / 2)
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

void	verti_loop( t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->vx = player->pos_xm;
	rays->vy = player->pos_ym;
	rays->dis_v = 1000000;
	rays->ntan = -tan(rays->ra);
	verti_check(map, player, rays);
	while (rays->dof < map->y - 2)
	{
		rays->vmrx = ((int)rays->rx / MINI_TILE) + rays->vshift;
		rays->vmry = ((int)rays->ry / MINI_TILE) + rays->vshift;
		if (rays->vmrx >= 0 && rays->vmrx < map->x
			&& rays->vmry >= 0 && rays->vmry < map->y
			&& map->scene[(int)rays->vmry]
			[(int)rays->vmrx] == '1')
		{
			printf("VY: %d, VX: %d\n", (int)rays->vmry, (int)rays->vmrx);
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->dis_v = dist(player, rays);
			rays->dof = map->y;
		}
		else
		{
			rays->rx += rays->xo;
			rays->ry += rays->yo;
			rays->dof += 1;
		}
	}
}

void	rays_comp(t_game *game, t_rays *rays)
{
	if (rays->dis_v < rays->dis_h)
	{
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->dist = rays->dis_v;
		rays->color = SIDE_WALL;
	}
	if (rays->dis_h < rays->dis_v)
	{
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->dist = rays->dis_h;
		rays->color = FRONT_WALL;
	}
	draw_line(&game->screen.map, (t_dline){
		game->player->pos_xm,
		game->player->pos_ym,
		game->player->rays.rx,
		game->player->rays.ry,
		0, 0, RED});
}

void	rays_fov(t_game *game, t_player *player, t_rays *rays)
{
	rays->r = -1;
	rays->ra = player->angle - DR * (FOV/2);
	reset_angle(rays);
	while (++rays->r < FOV)
	{
		hori_loop(game->map, player, rays);
		verti_loop(game->map, player, rays);
		rays_comp(game, rays);
		draw_ceiling(game, rays, rays->r);
		draw_floor(game, rays, rays->r);
		draw_wall(game, rays, rays->r);
		rays->ra += DR;
		reset_angle(rays);
	}
}
