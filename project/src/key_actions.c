/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:18:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 10:06:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_win(t_game *game)
{
	(void) game;
	printf("\n\033[1mYou've quit the game!\033[0m\n\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	show_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 0)
	{
		ft_printf("Minimap is enabled\n");
		game->screen.toggle_minimap = 1;
	}
	else
	{
		ft_printf("Minimap is disabled\n");
		game->screen.toggle_minimap = 0;
	}
	return (game->screen.toggle_minimap);
}

int	key_event(int key, t_game *game)
{
	if (key == K_MAC_ESCAPE || key == 65307)
		esc_win(game);
	if (key == K_MAC_M || key == 109)
		show_minimap(game);
	if (key == K_MAC_A || key == 97 || key == 65361 || key == 123)
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
		game->player->dir_x = cos(game->player->angle) * 5;
		game->player->dir_y = sin(game->player->angle) * 5;
	}
	if (key == K_MAC_D || key == 100 || key == 65363 || key == 124)
	{
		game->player->angle += 0.1;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
		game->player->dir_x = cos(game->player->angle) * 5;
		game->player->dir_y = sin(game->player->angle) * 5;
	}
	if (key == K_MAC_W || key == 119 || key == 65362 || key == 126)
	{
		game->player->pos_x += game->player->dir_x;
		game->player->pos_y += game->player->dir_y;
	}
	if (key == K_MAC_S || key == 115 || key == 65364 || key == 125)
	{
		game->player->pos_x -= game->player->dir_x;
		game->player->pos_y -= game->player->dir_y;
	}
	return (key);
}
