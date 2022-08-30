/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 02:37:08 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 01:27:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief
 *
 * Check Horizontal && Verticale Lines
 *
 * @param game
 * @param rays
 * @return int
 */

int	fpf_h_rays(t_player *player, t_img *img, t_map *map, t_rays *rays)
{
	(void) map;
	draw_ray(img, (t_line){
		player->pos_x,
		player->pos_y,
		rays->rx, rays->ry,
		0, 0, 0xfeca57});
	return (0);
}
