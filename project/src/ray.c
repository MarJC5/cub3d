/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:24:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/06 18:17:13 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(t_img *img, t_line line)
{
	float	pixel_x;
	float	pixel_y;
	int		pixels;

	pixels = sqrt((line.delta_x * line.delta_x)
			+ (line.delta_y * line.delta_y));
	line.delta_x /= pixels;
	line.delta_y /= pixels;
	pixel_x = line.posx;
	pixel_y = line.posy;
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
