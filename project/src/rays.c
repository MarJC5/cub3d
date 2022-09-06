/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/06 17:37:50 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	ray->wall_height = (TILE_SIZE * WIN_HEIGHT) / ray->dist;
	if (ray->wall_height > WIN_HEIGHT)
		ray->wall_height = WIN_HEIGHT;
	ray->wall_offset = 360 - ray->wall_height / 2;
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, ray->wall_offset,
		TILE_SIZE, TILE_SIZE, 0xcccccc});
	draw_rect(&game->screen.map, (t_rect){
		r * TILE_SIZE, ray->wall_height + ray->wall_offset,
		TILE_SIZE, TILE_SIZE, 0xcccccc});
}

void	rays_fov(t_game *game, t_player *player, t_rays *ray)
{
	ray->r = 0;
	ray->angle = player->angle - DR * 30;
	if (ray->angle < 0)
		ray->angle += 2 * M_PI;
	if (ray->angle > 2 * M_PI)
		ray->angle -= 2 * M_PI;
	while (ray->r < 60)
	{
		ray->dist = 0;
		ray->deltax = cos(ray->angle) * (SPEED / 2);
		ray->deltay = sin(ray->angle) * (SPEED / 2);
		ray->dist = draw_ray(game->map, &game->screen.map, (t_line){
				player->pos_xm, player->pos_ym,
				ray->deltax, ray->deltay,
				ray->dist, 0x2e86de}, game->screen.toggle_minimap);
		ray->dist *= (MINI_TILE + MAPOS);
		draw_wall(game, ray, ray->r);
		ray->angle += DR;
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		ray->r++;
	}
}
