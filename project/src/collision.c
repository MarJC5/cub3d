/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:53:29 by tpaquier          #+#    #+#             */
/*   Updated: 2022/09/06 18:27:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	collision(t_game *game)
{
	if (game->player->delta_xm > 0)
		game->col->x = COLLISION / 3;
	else
		game->col->x = -COLLISION / 3;
	if (game->player->delta_ym > 0)
		game->col->y = COLLISION / 3;
	else
		game->col->y = -COLLISION / 3;
	game->col->px = game->player->pos_xm + game->col->x;
	game->col->py = game->player->pos_ym + game->col->y;
	game->col->px = (game->col->px - MAPOS) / 8;
	game->col->py = (game->col->py - MAPOS) / 8;
	if (game->map->scene[game->col->py][game->col->px] == '1')
		return (1);
	return (0);
}

int	collision_bck(t_game *game)
{
	if (game->player->delta_xm > 0)
		game->col->x = COLLISION / 2;
	else
		game->col->x = -COLLISION / 2;
	if (game->player->delta_ym > 0)
		game->col->y = COLLISION / 2;
	else
		game->col->y = -COLLISION / 2;
	game->col->px = game->player->pos_xm - game->col->x;
	game->col->py = game->player->pos_ym - game->col->y;
	game->col->px = (game->col->px - MAPOS) / 8;
	game->col->py = (game->col->py - MAPOS) / 8;
	if (game->map->scene[game->col->py][game->col->px] == '1')
		return (1);
	return (0);
}

