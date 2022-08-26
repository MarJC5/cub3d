/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 09:19:28 by jmartin          ###   ########.fr       */
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

void	render_wrapper(t_img *img, int h, int w, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			img_pix_put(img, (j / SCALE) + MAPOS + 5,
						(i / SCALE) + MAPOS + 5, color);
			j++;
		}
		++i;
	}
}

int    fill_minimap(t_game *game, char tile, int color, float scale)
{
	int i;
	int j;

	i = 0;
	while (i < game->map->y)
	{
		j = 0;
		while (j < game->map->x)
		{
			if (game->map->scene[i][j] == tile)
				fpf_rect(&game->screen.img, (t_rect) {
						(j * scale) + MAPOS, (i * scale) + MAPOS,
						TILE_SIZE, TILE_SIZE, color});
			j++;
		}
		i++;
	}
	return (0);
}

void display_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 1)
	{
		fill_minimap(game, FLOOR, 0xCCdcdde1, TILE_SIZE);
		fill_minimap(game, WALL, 0xCC000000, TILE_SIZE);
		fill_minimap(game, EMPTY_ZONE, 0xCCFF0000, TILE_SIZE);
		fill_minimap(game, game->player->skin, 0xCCdcdde1, TILE_SIZE);
		fpf_circle(&game->screen.img, (t_circle) {
				(game->player->pos_x * TILE_SIZE + SCALE) + MAPOS,
				(game->player->pos_y * TILE_SIZE + (SCALE - 2)) + MAPOS,
				(TILE_SIZE / 2), chartohex("255, 63, 52", 255)});
	}
}