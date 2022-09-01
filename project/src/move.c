/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:57:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 22:36:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(t_game *game)
{
	game->player->angle -= 0.1;
	if (game->player->angle < 0)
		game->player->angle += 2 * PI;
	game->player->delta_xm = cos(game->player->angle) * (SPEED / 2);
	game->player->delta_ym = sin(game->player->angle) * (SPEED / 2);
	game->player->delta_x = cos(game->player->angle) * SPEED;
	game->player->delta_y = sin(game->player->angle) * SPEED;
}

void	move_right(t_game *game)
{
	game->player->angle += 0.1;
	if (game->player->angle > 2 * PI)
		game->player->angle -= 2 * PI;
	game->player->delta_xm = cos(game->player->angle) * (SPEED / 2);
	game->player->delta_ym = sin(game->player->angle) * (SPEED / 2);
	game->player->delta_x = cos(game->player->angle) * SPEED;
	game->player->delta_y = sin(game->player->angle) * SPEED;
}

void	move_up(t_game *game)
{
	game->player->pos_xm += game->player->delta_xm;
	game->player->pos_ym += game->player->delta_ym;
	game->player->pos_x += game->player->delta_x;
	game->player->pos_y += game->player->delta_y;
}

void	move_down(t_game *game)
{
	game->player->pos_xm -= game->player->delta_xm;
	game->player->pos_ym -= game->player->delta_ym;
	game->player->pos_x -= game->player->delta_x;
	game->player->pos_y -= game->player->delta_y;
}
