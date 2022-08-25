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

int	key_event(int key, t_game *game)
{
	if (key == K_ESCAPE)
		esc_win(game);
	return (key);
}
