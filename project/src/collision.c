/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:53:29 by tpaquier          #+#    #+#             */
/*   Updated: 2022/09/06 13:53:30 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	collision(t_game *game)
{
	int x;
	int y;
	int px;
	int py;

	if (game->player->delta_xm > 0)
		x = COLLISION / 2;
	else
		x = -COLLISION / 2;
	if (game->player->delta_ym > 0)
		y = COLLISION / 2;
	else
		y = -COLLISION / 2;
	
	px = game->player->pos_xm + x;
	py = game->player->pos_ym + y;
	px = (px - MAPOS) / 8;
	py = (py - MAPOS) / 8;
	if (game->map->scene[py][px] == '1')
		return(1);
	return (0);
}

int	collision_bck(t_game *game)
{
	int x;
	int y;
	int px;
	int py;

	if (game->player->delta_xm > 0)
		x = COLLISION / 2;
	else
		x = -COLLISION / 2;
	if (game->player->delta_ym > 0)
		y = COLLISION / 2;
	else
		y = -COLLISION / 2;
	px = game->player->pos_xm - x;
	py = game->player->pos_ym - y;
	px = (px - MAPOS) / 8;
	py = (py - MAPOS) / 8;
	if (game->map->scene[py][px] == '1')
		return(1);
	return (0);
}

