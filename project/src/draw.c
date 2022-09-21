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

void	draw_door(t_game *game, t_rays *ray, int r)
{
	int pos = (ray->wall_offset * 1 + r * (1 / 8));

	printf("POS :  %d\n", pos);

	char *mlx_data_addr = mlx_get_data_addr(game->text.img_n, &game->text.h, &game->text.w, &pos);

	printf("%d pour %d et %d %d\n", *(unsigned int *)mlx_data_addr, pos, game->text.h, game->text.w);
	
	draw_rect(&game->screen.map, (t_rect){
			r, ray->wall_offset,
			1, ray->wall_height, *(unsigned int *)mlx_data_addr});
}

void	draw_wall(t_game *game, t_rays *ray, int r)
{
	(void)r;
	ray->wall_height = (TILE_SIZE * WIN_HEIGHT) / (ray->dist * 4);
	if (ray->wall_height > WIN_HEIGHT)
		ray->wall_height = WIN_HEIGHT ;
	ray->wall_offset = (WIN_HEIGHT / 2.0) - ray->wall_height / 2;
	//printf("FILE : %p | %d | %d\n", game->text.img, game->text.h, game->text.w);
	if (ray->door == 1)
		draw_door(game, ray, r);
	else
		draw_rect(&game->screen.map, (t_rect){
			r, ray->wall_offset,
			1, ray->wall_height, ray->color});
}
