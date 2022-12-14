/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:49 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 15:36:56 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_tile(char *path, int x, int y, t_game *game)
{
	int		w;
	int		h;
	char	*img;

	img = mlx_xpm_file_to_image(game->screen.mlx, path, &w, &h);
	mlx_put_image_to_window(game->screen.mlx, game->screen.win, img, x, y);
}

int	init_map(t_game *game, char *file)
{
	if (check_map_name(game, file) == SUCCESS)
	{
		if (save_map_textures(game, -1, -1,
				get_next_line(game->map->fd)) == SUCCESS)
		{
			if (save_map(game, NULL,
					get_next_line(game->map->fd), 0) == SUCCESS)
			{
				save_map_scene(game, 0, 0, 0);
				check_player_pos(game, -1, -1);
				if (game->player->save != 1 || check_fd(game) == 1)
					return (FAILURE);
				if (printinvalid(check_map(game)) == ERR_UNCLOSED)
					return (FAILURE);
				print_map_details(game);
				init_screen(game);
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS); // PK Sucess
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
	game->text.x = 0;
	game->text.y = 0;
	game->text.img = NULL;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit(EXIT_FAILURE);
	game->s = 0;
	game->c = 0;
	game->k = 0;
	game->player->weapon.current = 1;
	game->player->weapon.frame = 0;
	game->player->weapon.has_weapon = 0;
}

void	init_view(t_game *game)
{
	game->screen.map.mlx_img = mlx_new_image(game->screen.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	game->screen.map.addr = mlx_get_data_addr(game->screen.map.mlx_img,
			&game->screen.map.bpp,
			&game->screen.map.line_len, &game->screen.map.endian);
	mlx_loop_hook(game->screen.mlx, &render_view, game);
	game->is_started = 0;
	play_sounds(game, SOUND_MENU);
	game->screen.welcome.mlx_img = mlx_new_image(game->screen.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	game->screen.welcome.addr = mlx_get_data_addr(game->screen.welcome.mlx_img,
			&game->screen.welcome.bpp,
			&game->screen.welcome.line_len, &game->screen.welcome.endian);
}

void	init_screen(t_game *game)
{
	game->screen.mlx = mlx_init();
	if (!game->screen.mlx)
		return ;
	game->screen.time = 0;
	game->screen.oldtime = 0;
	game->screen.oldx = WIN_WIDTH / 2;
	game->screen.toggle_minimap = 0;
	game->screen.toggle_audio = 0;
	game->screen.toggle_mouse = 0;
	game->screen.toggle_weapon = 0;
	game->screen.win = mlx_new_window(
			game->screen.mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	init_texture(game);
	init_weapon_knife(game);
	init_weapon_pistole(game);
	init_view(game);
	mlx_hook(game->screen.win, 2, 1L << 0, key_event, game);
	mlx_hook(game->screen.win, 6, 1L << 0, mouse_event, game);
	mlx_hook(game->screen.win, 17, 0L << 0, esc_win, game);
	mlx_loop(game->screen.mlx);
}
