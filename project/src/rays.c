/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 17:34:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line_ray(t_game *game)
{
	draw_line(&game->screen.map, (t_dline){
		game->player->pos_xm,
		game->player->pos_ym,
		game->player->rays.rx,
		game->player->rays.ry,
		0, 0, RED});
}

void	comp_v(t_rays *rays)
{
	if (rays->voldx != rays->vmrx || rays->voldy != rays->vmry)
		rays->rettest = 1;
}

void	rays_comp(t_game *game, t_rays *rays)
{
	if (rays->dis_v < rays->dis_h)
	{
		comp_v(rays);
		rays->voldx = rays->vmrx;
		rays->voldy = rays->vmry;
		rays->rx = rays->vx;
		rays->ry = rays->vy;
		rays->dist = rays->dis_v;
		rays->door = rays->doorv;
		init_orientation_v(game, rays);
	}
	if (rays->dis_h < rays->dis_v)
	{
		if (rays->oldx != rays->hmrx || rays->oldy != rays->hmry)
			rays->rettest = 1;
		rays->oldx = rays->hmrx;
		rays->oldy = rays->hmry;
		rays->rx = rays->hx;
		rays->ry = rays->hy;
		rays->dist = rays->dis_h;
		rays->door = rays->doorh;
		init_orientation(game, rays);
	}
	if (game->screen.toggle_minimap == 1)
		draw_line_ray(game);
}

void	rays_fov(t_game *game, t_player *player, t_rays *rays)
{
	rays->rettest = 0;
	rays->r = -1;
	rays->ra = player->angle - (float)degtorad(FOV) / 2.0;
	while (++rays->r < WIN_WIDTH)
	{
		reset_angle(rays);
		hori_loop(game->map, player, rays);
		verti_loop(game->map, player, rays);
		rays_comp(game, rays);
		draw_ceiling(game, rays, rays->r);
		draw_floor(game, rays, rays->r);
		draw_wall(game, rays, rays->r);
		rays->ra += (float)degtorad(FOV) / (float)WIN_WIDTH;
		fps(game);
	}
}
