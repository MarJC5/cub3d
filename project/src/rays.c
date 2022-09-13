/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/13 08:02:56 by jmartin          ###   ########.fr       */
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
	init_orientation(game);
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

void	reset_angle(t_game *game)
{
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
}

void	rays_fov(t_game *game, t_player *player, t_rays *ray)
{
	ray->r = 0;
	ray->angle = player->angle - DR * 30;
	reset_angle(game);
	while (ray->r < 180)
	{
		ray->dist = 0;
		ray->deltax = cos(ray->angle) * (SPEED / 2);
		ray->deltay = sin(ray->angle) * (SPEED / 2);
		ray->dist = draw_ray(game->map, &game->screen.map, (t_line){
				player->pos_xm, player->pos_ym,
				ray->deltax, ray->deltay,
				ray->dist, YELLOW}, game->screen.toggle_minimap);
		ray->dist *= (MINI_TILE + MAPOS) + 1;
		draw_floor(game, ray, ray->r);
		draw_ceiling(game, ray, ray->r);
		draw_wall(game, ray, ray->r);
		ray->angle += DR;
		reset_angle(game);
		ray->r++;
	}
}
