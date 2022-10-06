/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 07:32:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 12:25:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_floor(t_game *game, t_rays *ray, int r)
{
	(void)ray;
	draw_rect(&game->screen.map, (t_rect){
		r, WIN_HEIGHT / 2,
		1, WIN_HEIGHT / 2, chartohex(game->map->colors[0], 0)});
}

void	draw_ceiling(t_game *game, t_rays *ray, int r)
{
	(void)ray;
	draw_rect(&game->screen.map, (t_rect){
		r, 0,
		1, WIN_HEIGHT / 2, chartohex(game->map->colors[1], 0)});
}

void	fix_fisheye(t_game *game, t_rays *ray)
{
	float	ca;

	ca = game->player->angle - ray->ra;
	if (ca < 0)
		ca += 2 * M_PI;
	if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	ray->dist = ray->dist * cos(ca);
}

void	set_value(t_game *game, t_rays *ray, int r)
{
	int		pourc;
	float	test;

	game->text.count = 0;
	ray->wall_height = MINI_TILE / ray->dist * 640;
	game->text.pixel = ray->wall_height / SPRITE_SIZE;
	game->text.y2 = SPRITE_SIZE / 2;
	game->text.y = SPRITE_SIZE / 2;
	if (ray->door == 1)
		ray->text = 4;
	if (ray->dis_h < ray->dis_v)
		test = ray->rx / MINI_TILE;
	else
		test = ray->ry / MINI_TILE;
	pourc = (int)((test - (int)test) * 100);
	game->text.x = (SPRITE_SIZE * pourc) / 100;
	if (r == 0 || ray->rettest == 1 || game->text.x > SPRITE_SIZE)
	{
		game->text.x = 0;
		ray->rettest = 0;
	}
}

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	char	*pixel;

	fix_fisheye(game, ray);
	set_value(game, ray, r);
	game->text.addr = mlx_get_data_addr(game->text.img[ray->text],
			&game->text.bpp, &game->text.line_len, &game->text.endian);
	while (game->text.y >= 0 || game->text.y2 <= SPRITE_SIZE)
	{
		pixel = game->text.addr + (game->text.y2 * game->text.line_len
				+ game->text.x * (game->text.bpp / 8));
		if (game->text.y2 < SPRITE_SIZE)
			draw_rect(&game->screen.map, (t_rect){
				r, WIN_HEIGHT / 2 + game->text.count,
				1, game->text.pixel + 1, *(int *)pixel});
		pixel = game->text.addr + (game->text.y * game->text.line_len
				+ game->text.x * (game->text.bpp / 8));
		draw_rect(&game->screen.map, (t_rect){
			r, WIN_HEIGHT / 2 - game->text.count,
			1, game->text.pixel + 1, *(int *)pixel});
		game->text.y--;
		game->text.y2++;
		game->text.count = ((ray->wall_height / 1.0) / SPRITE_SIZE)
			* (game->text.y2 - SPRITE_SIZE / 2);
	}
}
