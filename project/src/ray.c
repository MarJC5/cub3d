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

double	draw_ray(t_map *map, t_img *img, t_line line)
{
	double	pixel_x;
	double	pixel_y;

	pixel_x = line.posx;
	pixel_y = line.posy;
	while (map->scene[(int)((pixel_y - MINI_TILE) / MINI_TILE)]
			[(int)((pixel_x - MINI_TILE) / MINI_TILE)] != '1')
	{
		img_pix_put(img, pixel_x, pixel_y, line.color);
		pixel_x += 0.2f * line.delta_x;
		pixel_y += 0.2f * line.delta_y;
		line.dist += 0.2f;
	}
	return (line.dist);
}
