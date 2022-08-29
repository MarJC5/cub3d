/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 02:50:28 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	fpf_ray(t_img *img, t_line line)
{
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	line.delta_x *= TILE_SIZE;
	line.delta_y *= TILE_SIZE;
	pixels = sqrt((line.delta_x * line.delta_x)
			+ (line.delta_y * line.delta_y));
	line.delta_x /= pixels;
	line.delta_y /= pixels;
	pixel_x = line.begin_x;
	pixel_y = line.begin_y;
	while (pixels)
	{
		img_pix_put(img, pixel_x, pixel_y, line.color);
		pixel_x += line.delta_x;
		pixel_y += line.delta_y;
		--pixels;
	}
	return (0);
}

int	fpf_draw_rays(t_game *game, t_img *img, t_rays rays)
{
	float	a_tan;

	while (rays.r++ < 1)
	{
		rays.dof = 0;
		a_tan = -1 / tan(rays.ra);
		if (rays.ra > PI)
		{
			rays.ry = (((int)game->player->pos_y >> 6) << 6) - 0.0001;
			rays.rx = (game->player->pos_y - rays.ry)
				* a_tan + game->player->pos_x;
			rays.yo = -game->map->size;
			rays.xo = -rays.yo * a_tan;
		}
		if (rays.ra < PI)
		{
			rays.ry = (((int)game->player->pos_y >> 6) << 6) + game->map->size;
			rays.rx = (game->player->pos_y - rays.ry)
				* a_tan + game->player->pos_x;
			rays.yo = game->map->size;
			rays.xo = -rays.yo * a_tan;
		}
		if (rays.ra == 0 || rays.ra == PI)
		{
			rays.rx = game->player->pos_x;
			rays.ry = game->player->pos_y;
			rays.dof = 8;
		}
		while (rays.dof < 8)
		{
			rays.mx = (int)(rays.rx) >> 6;
			rays.my = (int)(rays.ry) >> 6;
			rays.mp = rays.my * game->map->x + rays.mx;
			if (rays.mp < game->map->x * game->map->y
				&& game->map->map[rays.mp] == '1')
			{
				rays.dof = 8;
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;
				rays.dof += 1;
			}
		}
		fpf_ray(img, (t_line){
			(game->player->pos_x * TILE_SIZE) + TILE_SIZE / 2 + MAPOS,
			(game->player->pos_y * TILE_SIZE) + TILE_SIZE / 2 + MAPOS,
			rays.rx * TILE_SIZE,
			rays.ry * TILE_SIZE,
			chartohex("243, 156, 17", 0),
			game->player->dir_y, game->player->dir_x});
	}
	return (0);
}
