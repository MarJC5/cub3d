/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 19:37:02 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	fpf_ray(t_img *img, t_line line)
{
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	line.delta_x = (line.end_x - line.begin_x);
	line.delta_y = (line.end_y - line.begin_y);
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

/**
 * @brief 
 * 
 * Check Horizontal Lines
 * 
 * @param game 
 * @param rays 
 * @return int 
 */

int	fpf_draw_rays(t_game *game, t_rays *rays)
{
	double	a_tan;

	rays->r = 0;
	rays->ra = game->player->angle;
	while (rays->r++ < 1)
	{
		rays->dof = 0;
		a_tan = -1 / tan(rays->ra);
		if (rays->ra > PI)
		{
			rays->ry = (((int)(game->player->pos_y / game->map->size))
					* game->map->size) - 0.0001;
			rays->rx = (game->player->pos_y - rays->ry)
				* a_tan + game->player->pos_x;
			rays->yo = -game->map->size;
			rays->xo = -rays->yo * a_tan;
		}
		if (rays->ra < PI)
		{
			rays->ry = (((int)(game->player->pos_y / game->map->size))
					* game->map->size) + game->map->size;
			rays->rx = (game->player->pos_y - rays->ry)
				* a_tan + game->player->pos_x;
			rays->yo = game->map->size;
			rays->xo = -rays->yo * a_tan;
		}
		if (rays->ra == 0 || rays->ra == PI)
		{
			rays->rx = game->player->pos_x;
			rays->ry = game->player->pos_y;
			rays->dof = game->map->x;
		}
		while (rays->dof < game->map->x)
		{
			rays->mx = ((int)(rays->rx / game->map->size));
			rays->my = ((int)(rays->ry / game->map->size));
			rays->mp = rays->my * game->map->x + rays->mx;
			printf("HIT: %c\n", game->map->map[rays->mp]);
			if (rays->mp > 0
				&& rays->mp < game->map->size
				&& game->map->map[rays->mp] == '1')
			{
				rays->dof = game->map->x;
				printf("HIT: %c\n", game->map->map[rays->mp]);
			}
			else
			{
				rays->rx += rays->xo;
				rays->ry += rays->yo;
				rays->dof += 1;
			}
		}
		fpf_ray(&game->screen.map, (t_line){
			game->player->pos_x,
			game->player->pos_y,
			rays->rx, rays->ry,
			chartohex("243, 156, 17", 0), 0, 0});
	}
	return (0);
}
