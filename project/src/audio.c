/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:55:36 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 10:47:04 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	theme_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/theme.wav", NULL);
	}
}

static void	door_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/door_open.wav", NULL);
	}
}

static void	shot_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/weapon_pistol.wav", NULL);
	}
}

static void	cut_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/weapon_knife.wav", NULL);
	}
}

void	play_sounds(t_game *game, int sound_id)
{
	if (game->screen.toggle_audio == 1)
	{
		if (sound_id == SOUND_CUT)
			cut_sound();
		else if (sound_id == SOUND_SHOT)
			shot_sound();
		else if (sound_id == SOUND_DOOR)
			door_sound();
		else if (sound_id == SOUND_THEME)
			theme_sound();
		else if (sound_id == SOUND_MENU)
			menu_sound();
	}
}
