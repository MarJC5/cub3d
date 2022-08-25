/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 09:19:28 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    draw_rect(t_game *game, t_rect rect)
{
	int i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			mlx_pixel_put(
					game->screen->mlx,
					game->screen->win,
					j++, i, rect.color);
		}
		i++;
	}
}

void    fill_minimap(t_game *game, char tile, int color)
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
				draw_rect(game,
						  (t_rect){
							(j / 2.5) * MAPOS + MAPOS,
							(i / 2.5) * MAPOS + MAPOS,
							TILE_SIZE, TILE_SIZE, color});
			j++;
		}
		i++;
	}
}

void    init_minimap(t_game *game)
{
	fill_minimap(game, EMPTY_ZONE, 0xffffff);
	fill_minimap(game, WALL, 0x576574);
	fill_minimap(game, FLOOR, 0xdfe4ea);
}
