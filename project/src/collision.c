/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:53:29 by tpaquier          #+#    #+#             */
/*   Updated: 2022/09/08 16:43:46 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	collision(t_game *game)
{
	if (game->player->delta_xm > 0)
		game->col.x = COLLISION;
	else
		game->col.x = -COLLISION;
	if (game->player->delta_ym > 0)
		game->col.y = COLLISION ;
	else
		game->col.y = -COLLISION;
	game->col.px = game->player->pos_xm + game->col.x;
	game->col.py = game->player->pos_ym + game->col.y;
	game->col.px = (game->col.px - MAPOS) / MINI_TILE;
	game->col.py = (game->col.py - MAPOS) / MINI_TILE;
	if (game->map->scene[game->col.py][game->col.px] == DOOR)
		return (2);
	if (game->map->scene[game->col.py][game->col.px] == DOOR_OPEN)
		return (3);
	if (game->map->scene[game->col.py][game->col.px] == '1')
		return (1);
	return (0);
}

int	collision_left(t_game *game)
{
	float	dir;
	float	delta_x;
	float	delta_y;

	dir = game->player->angle + degtorad(90);
	delta_x = cos(dir) * SPEED;
	delta_y = sin(dir) * SPEED;
	if (delta_x > 0)
		game->col.x = -COLLISION;
	else
		game->col.x = COLLISION;
	if (delta_y > 0)
		game->col.y = -COLLISION;
	else
		game->col.y = COLLISION;
	game->col.px = game->player->pos_xm + game->col.x;
	game->col.py = game->player->pos_ym + game->col.y;
	game->col.px = (game->col.px - MAPOS) / MINI_TILE;
	game->col.py = (game->col.py - MAPOS) / MINI_TILE;
	if (game->map->scene[game->col.py][game->col.px] == '1' ||
		game->map->scene[game->col.py][game->col.px] == DOOR)
		return (1);
	return (0);
}

int	collision_right(t_game *game)
{
	float	dir;
	float	delta_x;
	float	delta_y;

	dir = game->player->angle + degtorad(90);
	delta_x = cos(dir) * SPEED;
	delta_y = sin(dir) * SPEED;
	if (delta_x > 0)
		game->col.x = COLLISION;
	else
		game->col.x = -COLLISION;
	if (delta_y > 0)
		game->col.y = COLLISION;
	else
		game->col.y = -COLLISION;
	game->col.px = game->player->pos_xm + game->col.x;
	game->col.py = game->player->pos_ym + game->col.y;
	game->col.px = (game->col.px - MAPOS) / MINI_TILE;
	game->col.py = (game->col.py - MAPOS) / MINI_TILE;
	if (game->map->scene[game->col.py][game->col.px] == '1' ||
		game->map->scene[game->col.py][game->col.px] == DOOR)
		return (1);
	return (0);
}

int	collision_bck(t_game *game)
{
	if (game->player->delta_xm > 0)
		game->col.x = COLLISION;
	else
		game->col.x = -COLLISION;
	if (game->player->delta_ym > 0)
		game->col.y = COLLISION;
	else
		game->col.y = -COLLISION;
	game->col.px = game->player->pos_xm - game->col.x;
	game->col.py = game->player->pos_ym - game->col.y;
	game->col.px = (game->col.px - MAPOS) / MINI_TILE;
	game->col.py = (game->col.py - MAPOS) / MINI_TILE;
	if (game->map->scene[game->col.py][game->col.px] == '1' ||
		game->map->scene[game->col.py][game->col.px] == DOOR)
		return (1);
	return (0);
}
