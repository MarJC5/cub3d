/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:18:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 14:24:01 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_win(t_game *game)
{
	(void)game;
	sound_kill();
	printf("\n\033[1mYou've quit the game!\033[0m\n\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	show_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 0)
		game->screen.toggle_minimap = 1;
	else
		game->screen.toggle_minimap = 0;
	return (game->screen.toggle_minimap);
}

static void	toggle_stuff(int key, t_game *game)
{
	if (key == K_MAC_P)
		toggle_mouse_visibility(game);
	if (key == K_MAC_V)
		toggle_audio(game);
	if (key == K_MAC_K)
		toggle_weapon(game);
}

static void	key_check(int key, t_game *game)
{
	if (key == K_MAC_M || key == 109)
		show_minimap(game);
	if (key == 123 || key == 65361)
		move_left(game);
	if (key == 124 || key == 65363)
		move_right(game);
	if (key == K_MAC_D || key == 100)
		move_fright(game);
	if (key == K_MAC_A || key == 97)
		move_fleft(game);
	if (key == K_MAC_W || key == 119 || key == 65362 || key == 126)
		move_up(game);
	if (key == K_MAC_S || key == 115 || key == 65364 || key == 125)
		move_down(game);
	if (key == K_MAC_E || key == 101)
		open_door(game);
	if (key == K_MAC_Q || key == 113)
		weapon_change(game);
	if (key == K_MAC_F || key == 102)
		weapon_use(game);
	toggle_stuff(key, game);
}

int	key_event(int key, t_game *game)
{
	fps(game);
	if (key == K_MAC_SP || key == 32)
	{
		if (game->is_started == 0)
		{
			sound_kill();
			play_sounds(game, SOUND_THEME);
		}
		game->is_started = 1;
	}
	if (key == K_MAC_ESCAPE || key == 65307)
		esc_win(game);
	if (game->is_started == 1)
		key_check(key, game);
	return (key);
}
