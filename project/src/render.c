/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 16:33:10 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_background(t_img *img, int floor, int ceilling)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			img_pix_put(img, j, i, ceilling);
			if (i > WIN_HEIGHT / 2)
				img_pix_put(img, j, i, floor);
			j++;
		}
		++i;
	}
}

static void	render_minimap_tile(t_game *game, char tile, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->y)
	{
		j = 0;
		while (j < game->map->x)
		{
			if (game->map->scene[i][j] == tile)
				draw_rect(&game->screen.map, (t_rect){
					(j * MINI_TILE) + MAPOS, (i * MINI_TILE) + MAPOS,
					MINI_TILE - 1, MINI_TILE - 1, color});
			j++;
		}
		i++;
	}
}

static void	setup_minimap(t_game *game)
{
	draw_ray(game->map, &game->screen.map, (t_line){
		game->player->pos_xm, game->player->pos_ym,
		game->player->delta_xm, game->player->delta_ym,
		0.0, WHITE}, 0);
	rays_fov(game, game->player, &game->player->rays);
}

void	render_map_view(t_game *game)
{
	setup_minimap(game);
	if (game->screen.toggle_minimap == 1)
	{
		render_minimap_tile(game, game->player->skin, WHITE);
		render_minimap_tile(game, FLOOR, WHITE);
		render_minimap_tile(game, WALL, BLACK);
		render_minimap_tile(game, DOOR, 0xcc8e35);
		render_minimap_tile(game, EMPTY_ZONE, 0xccBDC3C7);
		draw_line(&game->screen.map, (t_dline){
			game->player->pos_xm,
			game->player->pos_ym,
			game->player->pos_xm + game->player->delta_xm * 10,
			game->player->pos_ym + game->player->delta_ym * 10,
			0, 0, YELLOW});
		draw_circle(&game->screen.map, (t_circle){
			game->player->pos_xm,
			game->player->pos_ym,
			MINI_TILE / (SCALE / 1.5), RED});
	}
}

int	render_view(t_game *game)
{
	if (game->is_started == 0)
	{
		start_view(game);
		mlx_put_image_to_window(game->screen.mlx,
			game->screen.win, game->screen.welcome.mlx_img, 0, 0);
		return (game->is_started);
	}
	render_map_view(game);
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->screen.map.mlx_img, 0, 0);
	if (game->screen.toggle_minimap == 1)
		print_fps(game);
	return (SUCCESS);
}
