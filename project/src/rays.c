/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/15 15:10:22 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_floor(t_game *game, t_rays *ray, int r)
{
	int	c;
	int	wh;
	int	wo;

	wh = (TILE_SIZE * WIN_HEIGHT * 1.0) / ray->dist;
	wo = (WIN_HEIGHT / 2.0) - wh / 2;
	c = wh + wo;
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, c - TILE_SIZE * 3,
		TILE_SIZE, 816 - c, chartohex(game->map->colors[0], 0)});
}

void	draw_ceiling(t_game *game, t_rays *ray, int r)
{
	(void) ray;
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, 0,
		TILE_SIZE, 260, chartohex(game->map->colors[1], 0)});
}

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	ray->wall_height = (TILE_SIZE * WIN_HEIGHT * 1.0) / ray->dist;
	if (ray->wall_height > WIN_HEIGHT)
		ray->wall_height = WIN_HEIGHT;
	ray->wall_offset = (WIN_HEIGHT / 2.0) - ray->wall_height / 2;
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, ray->wall_offset - TILE_SIZE * 3,
		TILE_SIZE, ray->wall_height + 1, ray->color});
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, ray->wall_height + ray->wall_offset - TILE_SIZE * 3,
		TILE_SIZE, ray->wall_height, ray->color});
}

void	reset_angle(t_rays *ray)
{
	if (ray->angle > 2 * M_PI)
		ray->angle -= 2 * M_PI;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
}

void    hori_check(t_map *map, t_player *player, t_rays *rays)
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
	if (rays->ra < M_PI)
	{
		rays->ry = ((int)(player->pos_ym / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->rx = (player->pos_ym - rays->ry) * rays->atan + player->pos_xm;
		rays->yo = MINI_TILE;
		rays->hshift = -1;
		rays->xo = -rays->yo * rays->atan;
	}
	if (rays->ra == 0 || rays->ra == M_PI)
	{
		rays->rx = player->pos_xm;
		rays->ry = player->pos_ym;
		rays->dof = map->x;
	}
}

void    hori_loop(t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->dis_h = 1000000;
	rays->hx = player->pos_xm;
	rays->hy = player->pos_ym;
	rays->atan = -1 / tan(rays->ra);
	hori_check(map, player, rays);
	while (rays->dof < map->x)
	{
		rays->hmrx = ((int)rays->rx / MINI_TILE) + rays->hshift;
		rays->hmry = ((int)rays->ry / MINI_TILE) + rays->hshift;
		if (rays->hmrx >= 0 && rays->hmrx < map->x
			&& rays->hmry >= 0 && rays->hmry < map->y
			&& map->scene[(int)rays->hmry]
			[(int)rays->hmrx] == '1')
		{
			printf("H HIT\n");
			printf("y: %d x: %d\n", (int)rays->hmry, (int)rays->hmrx);
			rays->hx = rays->rx;
			rays->hy = rays->ry;
			rays->dis_h = sqrt(powf((rays->hx - player->pos_xm), 2)
					+ powf((rays->hy - player->pos_ym), 2));
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

void    verti_check(t_map *map, t_player *player, t_rays *rays)
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
	if (rays->ra < M_PI / 2 || rays->ra > 3 * M_PI / 2)
	{
		rays->rx = ((int)(player->pos_xm / MINI_TILE) * MINI_TILE) + MINI_TILE;
		rays->ry = (player->pos_xm - rays->rx) * rays->ntan + player->pos_ym;
		rays->xo = MINI_TILE;
		rays->vshift = -1;
		rays->yo = -rays->xo * rays->ntan;
	}
	if (rays->ra == 0 || rays->ra == M_PI)
	{
		rays->rx = player->pos_xm;
		rays->ry = player->pos_ym;
		rays->dof = map->y;
	}
}

void    verti_loop( t_map *map, t_player *player, t_rays *rays)
{
	rays->dof = 0;
	rays->dis_v = 1000000;
	rays->vx = player->pos_xm;
	rays->vy = player->pos_ym;
	rays->ntan = -tan(rays->ra);
	verti_check(map, player, rays);
	while (rays->dof < map->y)
	{
		rays->vmrx = ((int)rays->rx / MINI_TILE) + rays->vshift;
		rays->vmry = ((int)rays->ry / MINI_TILE) + rays->vshift;
		if (rays->vmrx >= 0 && rays->vmrx < map->x
			&& rays->vmry >= 0 && rays->vmry < map->y
			&& map->scene[(int)rays->vmry]
			[(int)rays->vmrx] == '1')
		{
			printf("V HIT\n");
			printf("y: %d x: %d\n", (int)rays->vmry, (int)rays->vmrx);
			rays->vx = rays->rx;
			rays->vy = rays->ry;
			rays->dis_v = sqrt(powf((rays->vx - player->pos_xm), 2)
					+ powf((rays->vy - player->pos_ym), 2));
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

void	rays_fov(t_game *game, t_player *player, t_rays *rays)
{
	rays->r = -1;
	rays->ra = player->angle;
	reset_angle(rays);
	while (++rays->r < 1)
	{
		hori_loop(game->map, player, rays);
		verti_loop(game->map, player, rays);
		if (rays->dis_v < rays->dis_h)
		{
			rays->rx = rays->vx;
			rays->ry = rays->vy;
			rays->color = YELLOW;
		}
		if (rays->dis_h < rays->dis_v)
		{
			rays->rx = rays->hx;
			rays->ry = rays->hy;
			rays->color = GREEN;
		}
		reset_angle(rays);
	}
}
