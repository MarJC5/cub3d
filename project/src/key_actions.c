/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:18:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 15:21:05 by jmartin          ###   ########.fr       */
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

int show_minimap(t_game *game)
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
	if (key == K_MAC_W || key == 119 || key == 65362)
		ft_printf("Key W - Up pressed\n", key);
	if (key == K_MAC_A || key == 97 || key == 65361)
		ft_printf("Key A - Left pressed\n", key);
	if (key == K_MAC_S || key == 115 || key == 65364)
		ft_printf("Key S - Down pressed\n", key);
	if (key == K_MAC_D || key == 100 || key == 65363)
		ft_printf("Key D - Right pressed\n", key);
	return (key);
}
