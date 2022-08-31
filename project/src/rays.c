/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/30 23:55:08 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray(t_map *map, t_screen *screen, t_player *player, t_rays *rays)
{
	rays->dist = draw_ray(map, &screen->map, (t_line){
		player->pos_xm, player->pos_ym,
		player->delta_x, player->delta_y, 0,
		chartohex("243, 156, 17", 0)});
}