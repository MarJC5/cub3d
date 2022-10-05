/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 07:44:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/05 07:45:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	weapon_change(t_game *game)
{
	if (game->player->weapon.current == 0)
	{
		printf("current weapon is: %s\n", "Knife");
		game->player->weapon.inuse = game->player->weapon.pistol[0];
		game->player->weapon.current++;
	}
	else if (game->player->weapon.current == 1)
	{
		printf("current weapon is: %s\n", "Pistol");
		game->player->weapon.current = 0;
		game->player->weapon.inuse = game->player->weapon.knife[0];
	}
	return (game->player->weapon.current);
}

int	weapon_action(t_game *game, int i)
{
	if (game->player->weapon.current == 1)
		game->player->weapon.inuse = game->player->weapon.pistol[i];
	else if (game->player->weapon.current == 0)
		game->player->weapon.inuse = game->player->weapon.knife[i];
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->player->weapon.inuse,
		(WIN_WIDTH / 2 - 128), (WIN_HEIGHT - 256));
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->player->weapon.inuse,
		(WIN_WIDTH / 2 - 128), (WIN_HEIGHT - 256));
	return (game->player->weapon.current);
}

int	weapon_release(t_game *game)
{
	double	now;
	double	compare;

	game->player->weapon.frame--;
	now = time_now();
	while (game->player->weapon.frame >= 0)
	{
		compare = time_now();
		if (compare - now > FRAME_TIME)
		{
			now = time_now();
			weapon_action(game, game->player->weapon.frame);
			game->player->weapon.frame--;
		}
	}
	return (game->player->weapon.frame);
}

int	weapon_use(t_game *game)
{
	double	now;
	double	compare;

	game->player->weapon.frame = 0;
	now = time_now();
	while (game->player->weapon.frame < 4)
	{
		compare = time_now();
		if (compare - now > FRAME_TIME)
		{
			now = time_now();
			weapon_action(game, game->player->weapon.frame);
			game->player->weapon.frame++;
		}
	}
	if (game->player->weapon.frame == 4)
		weapon_release(game);
	weapon_action(game, 0);
	return (game->player->weapon.frame);
}