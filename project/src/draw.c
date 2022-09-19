/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 07:32:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/19 07:33:02 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_floor(t_game *game, t_rays *ray, int r)
{
	(void) ray;
	/*int	c;
	int	wh;
	int	wo;

	wh = (TILE_SIZE * WIN_HEIGHT) / ray->dist;
	wo = (WIN_HEIGHT / 2.0) - wh / 2;
	c = wh + wo;*/
	draw_rect(&game->screen.map, (t_rect){
		r, WIN_HEIGHT / 2,
		TILE_SIZE, 360, chartohex(game->map->colors[0], 0)});
}

void	draw_ceiling(t_game *game, t_rays *ray, int r)
{
	(void) ray;
	draw_rect(&game->screen.map, (t_rect){
		r, 0,
		TILE_SIZE, 360, chartohex(game->map->colors[1], 0)});
}

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	ray->wall_height = (TILE_SIZE * WIN_HEIGHT) / (ray->dist *  4);
	if (ray->wall_height > WIN_HEIGHT)
		ray->wall_height = WIN_HEIGHT ;
	ray->wall_offset = (WIN_HEIGHT / 2.0) - ray->wall_height / 2;
	draw_rect(&game->screen.map, (t_rect){
		r, ray->wall_offset,
		TILE_SIZE, ray->wall_height, ray->color});
	draw_rect(&game->screen.map, (t_rect){
	  	r, ray->wall_offset,
	  	TILE_SIZE, ray->wall_height, ray->color});
}