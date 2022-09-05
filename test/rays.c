/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/05 18:34:30 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	perform_dda(t_map *map, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedx < ray->sidedy)
		{
			ray->sidedx += ray->deldx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedy += ray->deldy;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (map->scene[(int)ray->mapx][(int)ray->mapy] > '0')
			ray->hit = 1;
		if (ray->side == 1)
			ray->perp_walldist = ray->sidedx - ray->deldx;
		else
			ray->perp_walldist = ray->sidedy - ray->deldy;
		ray->lh = (int)(map->y / ray->perp_walldist);
		ray->draw_start = -ray->lh / 2 + map->y / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->lh / 2 + map->y / 2;
		if (ray->draw_end > map->y)
			ray->draw_end = map->y - 1;
		if (ray->side == 1)
			ray->color = ray->color / 2;
	}
}

void	side_and_step(t_player *player, t_raycast *ray)
{
	if (ray->raydx < 0)
	{
		ray->stepx = -1;
		ray->sidedx = (player->pos_x - ray->mapx) * ray->deldx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedx = (ray->mapx + 1.0 - player->pos_x) * ray->deldx;
	}
	if (ray->raydy < 0)
	{
		ray->stepy = -1;
		ray->sidedy = (player->pos_y - ray->mapy) * ray->deldy;
	}
	else
	{
		ray->stepy = -1;
		ray->sidedy = (ray->mapy + 1.0 - player->pos_y) * ray->deldy;
	}
}

void	init_ray(t_screen *screen, t_game *game, t_raycast *ray)
{
	int	x;

	x = 0;
	while (x++ < game->map->x)
	{
		ray->camx = 2 * x / (double)game->map->x - 1;
		ray->raydx = ray->dirx + ray->planex * ray->camx;
		ray->raydy = ray->diry + ray->planey * ray->camx;
		ray->mapx = (int)game->player->pos_x;
		ray->mapy = (int)game->player->pos_y;
		ray->color = 0xcccccc;
		if (ray->raydx == 0)
			ray->deldx = 1e30;
		else
			ray->deldx = (int)(1 / ray->raydx);
		if (ray->raydy == 0)
			ray->deldy = 1e30;
		else
			ray->deldy = (int)(1 / ray->raydy);
		ray->hit = 0;
		side_and_step(game->player, ray);
		perform_dda(game->map, ray);
		game->player->rays.dist = draw_player_ray(
				game->map, &screen->map, (t_line){
				game->player->pos_xm, game->player->pos_ym,
				game->player->delta_x, game->player->delta_y, 0.0,
				0x00b894});
	}
}
