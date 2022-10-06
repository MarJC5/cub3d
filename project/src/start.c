/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:38:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 07:44:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_control(t_game *game)
{
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (25 * MINI_TILE)) / 2,
		(WIN_HEIGHT + (15 * MINI_TILE)) / 2, MINI_TILE / 3, WHITE,
		"./assets/ascii/wasd.ascii",
		NULL, NULL, NULL, NULL, NULL, &game->screen.welcome});
}

void	start_view(t_game *game)
{
	render_background(&game->screen.welcome,
		BLACK, BLACK);
	init_ascii((t_art){
		0, 0, -1, 0,
		0, MINI_TILE, WHITE,
		"./assets/ascii/bg.ascii",
		NULL, NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (65 * MINI_TILE)) / 2,
		(WIN_HEIGHT - (50 * MINI_TILE)) / 2, MINI_TILE, WHITE,
		"./assets/ascii/start.ascii",
		NULL, NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (64 * MINI_TILE / 4)) / 2,
		(WIN_HEIGHT - (30 * MINI_TILE)) / 2, MINI_TILE / 6, WHITE,
		"./assets/ascii/creator.ascii",
		NULL, NULL, NULL, NULL, NULL, &game->screen.welcome});
	init_ascii((t_art){
		0, 0, -1, (WIN_WIDTH - (84 * MINI_TILE / 3)) / 2,
		(WIN_HEIGHT - (0 * MINI_TILE)) / 2, MINI_TILE / 3, WHITE,
		"./assets/ascii/run.ascii",
		NULL, NULL, NULL, NULL, NULL, &game->screen.welcome});
	draw_control(game);
}
