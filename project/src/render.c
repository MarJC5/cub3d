/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 01:51:47 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_background(t_img *img, int floor, int ceilling)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				img_pix_put(img, j, i, ceilling);
			else
				img_pix_put(img, j, i, floor);
			j++;
		}
		++i;
	}
}

void	render_minimap_tile(t_game *game, char tile, int color)
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
					(j * TILE_SIZE) + MAPOS, (i * TILE_SIZE) + MAPOS,
					TILE_SIZE - 1, TILE_SIZE - 1, color});
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 1)
	{
		render_minimap_tile(game, FLOOR, 0x33FFFFFF);
		render_minimap_tile(game, WALL, 0x000000);
		render_minimap_tile(game, EMPTY_ZONE, 0xBDC3C7);
		render_minimap_tile(game, game->player->skin, 0x33FFFFFF);
		draw_circle(&game->screen.map, (t_circle){
			game->player->pos_x,
			game->player->pos_y,
			TILE_SIZE / SCALE, chartohex("192, 57, 43", 0)});
	}
}

int	render_view(t_game *game)
{
	render_background(&game->screen.map,
		chartohex(game->map->colors[0], 0),
		chartohex(game->map->colors[1], 0));
	render_minimap(game);
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->screen.map.mlx_img, 0, 0);
	return (0);
}
