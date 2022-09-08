/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:38:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/08 15:51:59 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	start_view(t_game *game)
{
	render_background(&game->screen.welcome,
		0xf2f2f2, 0xf2f2f2);
	init_ascii((t_art){
		0, 0, -1, 0,
		0, MINI_TILE, WHITE,
		"./assets/ascii/bg.ascii",
		NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (65 * MINI_TILE)) / 2,
		(WIN_HEIGHT - (8 * MINI_TILE)) / 2, MINI_TILE, WHITE,
		"./assets/ascii/start.ascii",
		NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (64 * MINI_TILE / 4)) / 2,
		(WIN_HEIGHT - (15 * MINI_TILE)) / 2, MINI_TILE / 6, WHITE,
		"./assets/ascii/creator.ascii",
		NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (84 * MINI_TILE / 3)) / 2,
		(WIN_HEIGHT - (15 * MINI_TILE)) / 2, MINI_TILE / 3, WHITE,
		"./assets/ascii/run.ascii",
		NULL, NULL, NULL, NULL, &game->screen.welcome});
}
