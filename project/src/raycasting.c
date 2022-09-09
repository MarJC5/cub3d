/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/09 13:09:57 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_orientation(t_game *game)
{
	if (game->player->rays.angle > 0
		&& game->player->rays.angle < degtorad(180))
		printf("Looking UP\n");
	else if (game->player->rays.angle > degtorad(180))
		printf("Looking DOWN\n");
	else
		printf("Looking LEFT - RIGHT\n");
	if (game->player->rays.angle > degtorad(90)
		&& game->player->rays.angle < degtorad(270))
	{
		printf("Looking LEFT\n");
	}
	else if (game->player->rays.angle < degtorad(90)
		|| game->player->rays.angle > degtorad(270))
		printf("Looking RIGHT\n");
	else
		printf("Looking UP - DOWN\n");
}
