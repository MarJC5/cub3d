/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:18:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/05 18:46:30 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#define FRAME_TIME 50.0

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
		if (key == K_MAC_Q || key == 113)
			weapon_change(game);
		if (key == K_MAC_F || key == 102)
			weapon_use(game);
	}
	return (key);
}
