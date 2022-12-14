/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:24:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 14:40:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(t_img *img, t_dline line)
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

float	draw_ray(t_map *map, t_img *img, t_line line, int active)
{
	float	pixel_x;
	float	pixel_y;

	pixel_x = line.posx;
	pixel_y = line.posy;
	if (pixel_x < 0 || pixel_y < 0)
		return (0.0);
	while (map->scene[(int)((pixel_y - MINI_TILE) / MINI_TILE)]
		[(int)((pixel_x - MINI_TILE) / MINI_TILE)] != '1')
	{
		if (active)
			img_pix_put(img, pixel_x, pixel_y, line.color);
		pixel_x += 0.1f * line.delta_x;
		pixel_y += 0.1f * line.delta_y;
		line.dist += 0.1f;
	}
	return (line.dist);
}
