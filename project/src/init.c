/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:49 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/06 10:10:08 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_map(t_game *game, char *file)
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
				if (printinvalid(check_map(game)) == ERR_UNCLOSED)
					return (FAILURE);
				check_player_pos(game, 0, -1);
				print_map_details(game);
				init_screen(game);
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
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
	game->screen.toggle_minimap = 1;
	game->screen.win = mlx_new_window(
			game->screen.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	init_view(game);
	mlx_hook(game->screen.win, 2, 1L << 0, key_event, game);
	mlx_hook(game->screen.win, 17, 0L << 0, esc_win, game);
	mlx_loop(game->screen.mlx);
}
