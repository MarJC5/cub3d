/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:24:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/31 00:16:47 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_ray(t_img *img, t_line line)
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
}

void	step_dist(t_map *map, t_player *player, t_rays *rays)
{
	if (rays->dir_x < 0)
	{
		rays->step_x = -1;
		rays->side_dist_x = (player->pos_x - map->map_x) * rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = (map->map_x + 1.0 - player->pos_x)
			* rays->delta_dist_x;
	}
	if (rays->dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (player->pos_y - map->map_y) * rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = (map->map_y + 1.0 - player->pos_y)
			* rays->delta_dist_y;
	}
}

void	dda_algo(t_map *map, t_rays *rays)
{
	while (rays->hit == 0)
	{
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			map->map_x += rays->step_x;
			rays->side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			map->map_y += rays->step_y;
			rays->side = 1;
		}
		if (map->scene[map->map_x][map->map_y] != '1')
		{
			printf("insite");
			rays->hit = 1;
		}
	}
}

void	init_ray(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	int	w;

	w = -1;
	while (++w < map->x)
	{
		screen->camera_x = 2 * w / (double) w - 1;
		rays->dir_x = player->pos_x
			+ screen->plane_x * screen->camera_x;
		rays->dir_y = player->pos_y
			+ screen->plane_y * screen->camera_x;
		map->map_x = (int) player->pos_x;
		map->map_y = (int) player->pos_y;
		if (rays->dir_x == 0)
			rays->delta_dist_x = 1e30;
		else
			rays->delta_dist_x = (int)(1 / rays->dir_x);
		rays->hit = 0;
		step_dist(map, player, rays);
		dda_algo(map, rays);
		if (rays->side == 0)
			rays->pp_wall_dist = (rays->side_dist_x - rays->delta_dist_x);
		else
			rays->pp_wall_dist = (rays->side_dist_y - rays->delta_dist_y);
		rays->line_h = (int)(map->y / rays->pp_wall_dist);
		rays->draw_start = -rays->line_h / 2 + map->y / 2;
		if (rays->draw_start < 0)
			rays->draw_start = 0;
		rays->draw_end = rays->line_h / 2 + map->y / 2;
		if (rays->draw_end >= map->y)
			rays->draw_end = map->y - 1;
		/*draw_ray(&screen->map, (t_line){
			player->pos_x,
			player->pos_y,
			rays->draw_start, rays->draw_end,
			0, 0, 0xfeca57});*/
	}
}
