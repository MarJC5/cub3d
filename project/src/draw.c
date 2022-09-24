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
	if (ray->door == 1)
	{
		int c = ray->wall_height / SPRITE_SIZE;
		int c2 = 0;
		if (game->text.c == 0) //sauvegarde combien de pixel en largeur avec l'offset du premier rayon pour ceux d'après (jusqu'au dernier rayon)
			game->text.c2 = ray->wall_height / SPRITE_SIZE;
		game->text.y = 0;
		while (c2 < ray->wall_height)
		{
			game->text.addr = mlx_get_data_addr(game->text.img_d, &game->text.bpp,
				&game->text.line_len, &game->text.endian);
			pixel = game->text.addr + (game->text.y * game->text.line_len
				+ game->text.x * (game->text.bpp / 8));
			draw_rect(&game->screen.map, (t_rect){
				r, (int)ray->wall_offset,
				1, c, *(int *)pixel});
			ray->wall_offset += c;
			c2 += c;
			game->text.y++;
		}
		if (game->text.c > (game->text.c2 - 1) && game->text.x < SPRITE_SIZE) // change de pixel en largeur + reset les valeurs pck fin du mur
		{
			game->text.x++;
			game->text.c = 0;
		}
		game->text.c++;
		printf("%d || %d || %d\n", game->text.x, game->text.c2, game->text.c);
	}
	else
	{
		game->text.c = 0;
		game->text.x = 0;
		draw_rect(&game->screen.map, (t_rect){
			r, ray->wall_offset,
			1, ray->wall_height, ray->color});
	}
}
