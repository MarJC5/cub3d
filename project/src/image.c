/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:44 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 18:57:12 by jmartin          ###   ########.fr       */
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
			img_pix_put(img, j, i, color);
			j++;
		}
		++i;
	}
}

int	fill_minimap(t_game *game, char tile, int color)
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
				fpf_rect(&game->screen.map, (t_rect){
					(j * TILE_SIZE) + MAPOS, (i * TILE_SIZE) + MAPOS,
					TILE_SIZE - 1, TILE_SIZE - 1, color});
			j++;
		}
		i++;
	}
	return (0);
}

void	display_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 1)
	{	
		fill_minimap(game, FLOOR, 0x33FFFFFF);
		fill_minimap(game, WALL, 0x000000);
		fill_minimap(game, EMPTY_ZONE, 0xBDC3C7);
		fill_minimap(game, game->player->skin, 0x33FFFFFF);
		fpf_draw_rays(game, game->player->rays);
		fpf_circle(&game->screen.map, (t_circle){
			game->player->pos_x,
			game->player->pos_y,
			TILE_SIZE / SCALE, chartohex("192, 57, 43", 0)});
	}
}
