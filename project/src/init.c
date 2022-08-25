/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:21:29 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 18:41:22 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_screen(t_game *game)
{
	game->screen = malloc(sizeof(t_screen));
	if (!game->screen)
		return ;
	game->screen->mlx = mlx_init();
	game->screen->win = mlx_new_window(
			game->screen->mlx,
			WIN_WIDTH,
			WIN_HEIGHT,
			WIN_NAME);
	init_minimap(game);
	mlx_hook(game->screen->win, 2, 1L << 0, key_event, game);
	mlx_hook(game->screen->win, 17, 0L << 0, esc_win, game);
	mlx_loop(game->screen->mlx);
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
	game->player->pos_x = -1;
	game->player->pos_y = -1;
}
