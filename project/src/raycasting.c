/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 11:59:35 by jmartin          ###   ########.fr       */
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

float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}

int	fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

float distance(int ax, int ay, int bx, int by, int ang)
{
	return (cos(deg_to_rad(ang)) * (bx - ax)
		- sin(deg_to_rad(ang)) * (by - ay));
}

int	fpf_draw_rays(t_game *game, t_img *img, t_rays rays)
{
	float	a_tan;

	while (rays.r < 60)
	{
		rays.dof = 0;
		a_tan = -1 / tan(rays.ra);
		if (rays.ra > M_PI)
		{
			rays.ry = ((int)(game->player->pos_y / game->map->size))
				* game->map->size - 0.0001;
			rays.rx = (game->player->pos_y - rays.ry)
				* a_tan + game->player->pos_x;
			rays.yo = -game->map->size;
			rays.xo = -rays.yo * a_tan;
		}
		if (rays.ra < M_PI)
		{
			rays.ry = ((int)(game->player->pos_y / game->map->size))
				* game->map->size + game->map->size;
			rays.rx = (game->player->pos_y - rays.ry)
				* a_tan + game->player->pos_x;
			rays.yo = game->map->size;
			rays.xo = -rays.yo * a_tan;
		}
		if (rays.ra == 0 || rays.ra == M_PI)
		{
			rays.rx = game->player->pos_x;
			rays.ry = game->player->pos_y;
			rays.dof = game->map->x;
		}
		while (rays.dof < game->map->x)
		{
			rays.mx = ((int)(rays.rx / game->map->size));
			rays.my = ((int)(rays.ry / game->map->size));
			rays.mp = rays.my * game->map->x + rays.mx;
			if (rays.mp > 0 && rays.mp < game->map->x * game->map->y
				&& game->map->map[rays.mp] == '1')
			{
				rays.dof = game->map->x;
				rays.dis_h = cos(deg_to_rad(rays.ra))
					* (rays.rx - game->player->pos_x)
					- sin(deg_to_rad(rays.ra))
					* (rays.ry - game->player->pos_y);
			}
			else
			{
				rays.rx += rays.xo;
				rays.ry += rays.yo;
				rays.dof += 1;
			}
		}
		fpf_ray(img, (t_line){
			game->player->pos_x,
			game->player->pos_y,
			rays.rx,
			rays.ry,
			chartohex("243, 156, 17", 0),
			game->player->dir_y, game->player->dir_x});
		rays.r++;
	}
	return (0);
}
