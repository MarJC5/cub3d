/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:24:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 01:26:02 by jmartin          ###   ########.fr       */
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
