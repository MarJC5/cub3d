/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:57:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 10:52:20 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_up(t_game *game)
{
	if (collision(game) == 0 || collision(game) == 3)
	{
		game->player->pos_xm += game->player->delta_xm;
		game->player->pos_ym += game->player->delta_ym;
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}

void	move_down(t_game *game)
{
	if (collision_bck(game) == 0 || collision_bck(game) == 3)
	{
		game->player->pos_xm -= game->player->delta_xm;
		game->player->pos_ym -= game->player->delta_ym;
		game->player->pos_x = (int)game->player->pos_xm / MINI_TILE;
		game->player->pos_y = (int)game->player->pos_ym / MINI_TILE;
	}
}
