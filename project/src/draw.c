/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 07:32:38 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/19 17:34:51 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void	draw_floor(t_game *game, t_rays *ray, int r)
{
	(void) ray;
	/*int	c;
	int	wh;
	int	wo;

	wh = (TILE_SIZE * WIN_HEIGHT) / ray->dist;
	wo = (WIN_HEIGHT / 2.0) - wh / 2;
	c = wh + wo;*/
	draw_rect(&game->screen.map, (t_rect){
		r, WIN_HEIGHT / 2,
		1, WIN_HEIGHT / 2, chartohex(game->map->colors[0], 0)});
}

void	draw_ceiling(t_game *game, t_rays *ray, int r)
{
	(void) ray;
	draw_rect(&game->screen.map, (t_rect){
		r, 0,
		1, WIN_HEIGHT / 2, chartohex(game->map->colors[1], 0)});
}

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	char *pixel;

	ray->wall_height = (TILE_SIZE * WIN_HEIGHT) / (ray->dist * 4.0);
	if (ray->wall_height > WIN_HEIGHT)
		ray->wall_height = WIN_HEIGHT;
	ray->wall_offset = (WIN_HEIGHT / 2.0) - ray->wall_height / 2.0;
	//printf("FILE : %p | %d | %d\n", game->text.img, game->text.h, game->text.w);
	if (ray->door == 1)
	{
		int y = 0;
		int c = ray->wall_height / SPRITE_SIZE;
		int c2 = 0;

		printf("%d\n", c);
		while (c2 < ray->wall_height)
		{
			game->text.addr = mlx_get_data_addr(game->text.img_w, &game->text.bpp,
				&game->text.line_len, &game->text.endian);
			pixel = game->text.addr + (y * game->text.line_len
				+ game->text.x * (game->text.bpp / 8));
			draw_rect(&game->screen.map, (t_rect){
				r, ray->wall_offset,
				1, c, *(int *)pixel});
			ray->wall_offset += c;
			c2 += c;
			y++;
			if (y > SPRITE_SIZE)
				y = 0;
		}
		// rajouter un if pour incrementer x que quand "largeur du mur / sprite_size" sera fait
		game->text.x += 1;
		if (game->text.x > SPRITE_SIZE)
			game->text.x = 0;
	}
	else
	{
		game->text.x = 0;
		draw_rect(&game->screen.map, (t_rect){
			r, ray->wall_offset,
			1, ray->wall_height, ray->color});
	}
}
