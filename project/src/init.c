/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:49 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 22:57:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_game *game, char *file)
{
	if (check_map_name(game, file) == SUCCESS)
	{
		if (save_map_textures(game, -1, 0,
				get_next_line(game->map->fd)) == SUCCESS)
		{
			if (save_map(game, NULL,
					get_next_line(game->map->fd), 0) == SUCCESS)
			{
				save_map_scene(game, 0, 0, 0);
				check_player_pos(game);
				print_map_details(game);
				init_screen(game);
			}
		}
	}
}


void    init_collision(t_player *player, t_map *map)
{
	player->collision.xo = 0;
	if (player->delta_x < 0)
		player->collision.xo = -20;
	else
		player->collision.xo = 20;
	player->collision.yo = 0;
	if (player->delta_y < 0)
		player->collision.yo = -20;
	else
		player->collision.yo = 20;
	player->collision.ipx = player->pos_x / map->size;
	player->collision.ipx_add_xo = (player->pos_x + player->collision.xo) / map->size;
	player->collision.ipx_sub_xo = (player->pos_x - player->collision.xo) / map->size;
	player->collision.ipy = player->pos_y / map->size;
	player->collision.ipy_add_yo = (player->pos_y + player->collision.yo) / map->size;
	player->collision.ipy_sub_yo = (player->pos_y - player->collision.yo) / map->size;
}

void	init_default(t_game *game)
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
	init_collision(game->player, game->map);
}

void	init_view(t_game *game)
{
	game->screen.map.mlx_img = mlx_new_image(game->screen.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	game->screen.map.addr = mlx_get_data_addr(game->screen.map.mlx_img,
			&game->screen.map.bpp,
			&game->screen.map.line_len, &game->screen.map.endian);
	mlx_loop_hook(game->screen.mlx, &render_view, game);
}

void	init_screen(t_game *game)
{
	game->screen.mlx = mlx_init();
	if (!game->screen.mlx)
		return ;
	game->screen.time = 0.0;
	game->screen.old_time = 0.0;
	game->screen.plane_x = 0.0;
	game->screen.plane_y = 0.66;
	game->screen.toggle_minimap = 1;
	game->screen.win = mlx_new_window(
			game->screen.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	init_view(game);
	mlx_hook(game->screen.win, 2, 1L << 0, key_event, game);
	mlx_hook(game->screen.win, 17, 0L << 0, esc_win, game);
	mlx_loop(game->screen.mlx);
}
