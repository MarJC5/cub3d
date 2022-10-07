/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:40:06 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 18:56:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	toggle_audio(t_game *game)
{
	if (game->screen.toggle_audio == 1)
	{
		game->screen.toggle_audio = 0;
		sound_kill();
	}
	else if (game->screen.toggle_audio == 0)
	{
		game->screen.toggle_audio = 1;
		play_sounds(game, SOUND_THEME);
	}
}

void	open_door(t_game *game)
{
	int	door;

	door = collision(game);
	if (door == 2)
	{
		play_sounds(game, SOUND_DOOR);
		game->map->scene[game->col.py][game->col.px] = DOOR_OPEN;
	}
	if (door == 3)
	{
		play_sounds(game, SOUND_DOOR);
		game->map->scene[game->col.py][game->col.px] = DOOR;
	}
}

void	toggle_weapon(t_game *game)
{
	if (game->screen.toggle_weapon == 1)
	{
		game->screen.toggle_weapon = 0;
	}
	else if (game->screen.toggle_weapon == 0)
	{
		game->screen.toggle_weapon = 1;
	}
}
