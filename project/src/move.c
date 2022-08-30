/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:57:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 01:57:51 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_left(t_game *game)
{
	game->player->angle -= 0.1;
	if (game->player->angle < 0)
		game->player->angle += 2 * M_PI;
	game->player->dir_x = cos(game->player->angle) * SPEED;
	game->player->dir_y = sin(game->player->angle) * SPEED;
}

void	move_right(t_game *game)
{
	game->player->angle += 0.1;
	if (game->player->angle > 2 * M_PI)
		game->player->angle -= 2 * M_PI;
	game->player->dir_x = cos(game->player->angle) * SPEED;
	game->player->dir_y = sin(game->player->angle) * SPEED;
}

void	move_up(t_game *game)
{
	game->player->pos_x += game->player->dir_x;
	game->player->pos_y += game->player->dir_y;
}

void	move_down(t_game *game)
{
	game->player->pos_x -= game->player->dir_x;
		game->player->pos_y -= game->player->dir_y;
}
