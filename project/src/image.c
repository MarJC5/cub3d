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
			img_pix_put(img, j + (MAPOS / 2), i + (MAPOS / 2), color);
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
				fpf_rect(&game->screen.img, (t_rect){
						(j / scale) * MAPOS + MAPOS,
						(i / scale) * MAPOS + MAPOS,
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
		render_wrapper(&game->screen.img, game->map->y * TILE_SIZE + 20,
		               game->map->x * TILE_SIZE + 12, 0x80FF0000);
		fill_minimap(game, EMPTY_ZONE, 0xCCFF0000, 2.5);
		fill_minimap(game, FLOOR, 0xCCdcdde1, 2.5);
		fill_minimap(game, WALL, 0xCC000000, 2.5);
	}
}