/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:18:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 18:01:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_win(t_game *game)
{
	ft_free_multitab_void(game->text.img);
	ft_free_multitab_void(game->player->weapon.knife);
	ft_free_multitab_void(game->player->weapon.pistol);
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

int	mouse_event(int x, int y, t_game *game)
{
	(void) y;
	if (x < game->screen.oldx && x > 0)
	{
		game->screen.oldx = x;
		move_left(game);
	}
	else if (x > game->screen.oldx && x < WIN_WIDTH)
	{
		game->screen.oldx = x;
		move_right(game);
	}
	return (x);
}

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
	return (game->player->weapon.current);
}

int	weapon_use(t_game *game)
{
	double	now;

	game->player->weapon.frame = 0;
	now = game->screen.time;
	while (game->player->weapon.frame < 4)
	{
		current_timestamp(game);
		if (game->screen.time - now > 3.0)
		{
			now = game->screen.time;
			weapon_action(game, game->player->weapon.frame++);
		}

	}
	return (game->player->weapon.frame);
}

int	key_event(int key, t_game *game)
{
	fps(game);
	if (key == K_MAC_SP || key == 32)
		game->is_started = 1;
	if (key == K_MAC_ESCAPE || key == 65307)
		esc_win(game);
	if (game->is_started == 1)
	{
		if (key == K_MAC_M || key == 109)
			show_minimap(game);
		if (key == K_MAC_A || key == 97 || key == 65361 || key == 123)
			move_left(game);
		if (key == K_MAC_D || key == 100 || key == 65363 || key == 124)
			move_right(game);
		if (key == K_MAC_W || key == 119 || key == 65362 || key == 126)
			move_up(game);
		if (key == K_MAC_S || key == 115 || key == 65364 || key == 125)
			move_down(game);
		if (key == K_MAC_E || key == 101)
			open_door(game);
		if (key == K_MAC_Q)
			weapon_change(game);
		if (key == K_MAC_F)
			weapon_use(game);
	}
	return (key);
}
