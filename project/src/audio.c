/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:55:36 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 06:52:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	theme_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/theme.wav", NULL);
	}
}

void	door_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/door_open.wav", NULL);
	}
}

void	shot_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/weapon_pistol.wav", NULL);
	}
}

void	cut_sound(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execlp("afplay", "afplay", "-v", "0.2",
			"./assets/sounds/weapon_knife.wav", NULL);
	}
}

void	weapon_sounds(int sound_id)
{
	if (sound_id == 0)
		cut_sound();
	else if (sound_id == 1)
		shot_sound();
}
