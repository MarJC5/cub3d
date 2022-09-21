/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:57:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/06 10:39:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(t_game *game)
{
	game->player->angle -= 0.1;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	game->player->delta_xm = cos(game->player->angle) * (SPEED / 2);
	game->player->delta_ym = sin(game->player->angle) * (SPEED / 2);
	game->player->delta_x = cos(game->player->angle) * SPEED;
	game->player->delta_y = sin(game->player->angle) * SPEED;
}

void	move_right(t_game *game)
{
	game->player->angle += 0.1;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	game->player->delta_xm = cos(game->player->angle) * (SPEED / 2);
	game->player->delta_ym = sin(game->player->angle) * (SPEED / 2);
	game->player->delta_x = cos(game->player->angle) * SPEED;
	game->player->delta_y = sin(game->player->angle) * SPEED;
}

void	move_up(t_game *game)
{
	if (collision(game) == 0)
	{
		game->player->pos_xm += game->player->delta_xm;
		game->player->pos_ym += game->player->delta_ym;
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}

void	move_down(t_game *game)
{
	if (collision_bck(game) == 0)
	{
		game->player->pos_xm -= game->player->delta_xm;
		game->player->pos_ym -= game->player->delta_ym;
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}

void	open_door(t_game *game)
{
	if (collision(game) == 2)
	{
		game->map->scene[game->col.py][game->col.px] = 3;
	}
}
