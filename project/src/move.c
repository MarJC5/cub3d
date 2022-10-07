/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:57:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 10:52:56 by jmartin          ###   ########.fr       */
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

void	move_fleft(t_game *game)
{
	if (collision(game) == 0)
	{
		game->player->dir = game->player->angle + degtorad(90);
		game->player->delta_x = cos(game->player->dir) * SPEED;
		game->player->delta_y = sin(game->player->dir) * SPEED;
		game->player->pos_xm -= cos(game->player->dir) * (SPEED / 2);
		game->player->pos_ym -= sin(game->player->dir) * (SPEED / 2);
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}

void	move_fright(t_game *game)
{
	if (collision_right(game) == 0)
	{
		game->player->dir = game->player->angle + degtorad(90);
		game->player->delta_x = cos(game->player->dir) * SPEED;
		game->player->delta_y = sin(game->player->dir) * SPEED;
		game->player->pos_xm += cos(game->player->dir) * (SPEED / 2);
		game->player->pos_ym += sin(game->player->dir) * (SPEED / 2);
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}
