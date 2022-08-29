/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:49 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 10:33:13 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_screen(t_game *game)
{
	game->screen.mlx = mlx_init();
	if (!game->screen.mlx)
		return ;
	game->screen.win = mlx_new_window(
			game->screen.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	init_map_preset(game);
	mlx_hook(game->screen.win, 2, 1L << 0, key_event, game);
	mlx_hook(game->screen.win, 17, 0L << 0, esc_win, game);
	mlx_loop(game->screen.mlx);
}

void	init_map_var(t_game *game)
{
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		exit(EXIT_FAILURE);
	game->map->colors = ft_calloc(3, sizeof(char *));
	game->map->assets = ft_calloc(5, sizeof(char *));
	game->map->identifier = ft_calloc(7, sizeof(char *));
	if (!game->map->colors || !game->map->assets || !game->map->identifier)
		exit(EXIT_FAILURE);
	game->map->map = NULL;
	game->map->scene = NULL;
	game->map->fd = -1;
	game->map->x = -1;
	game->map->y = -1;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit(EXIT_FAILURE);
	game->player->is_ready = 0;
	game->player->pos_x = 0.0;
	game->player->pos_y = 0.0;
	game->player->angle = 0.0;
	game->player->dir_x = cos(game->player->angle) * 5;
	game->player->dir_y = sin(game->player->angle) * 5;
	game->player->time = 0.0;
	game->player->old_time = 0.0;
	game->screen.toggle_minimap = 1;
}
