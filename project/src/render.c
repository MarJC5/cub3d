/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/15 14:59:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	render_background(t_img *img, int floor, int ceilling)
{
	int		i;
	int		j;

	(void) floor;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			img_pix_put(img, j, i, ceilling);
			j++;
		}
		++i;
	}
}

void	render_minimap_tile(t_game *game, char tile, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->y)
	{
		j = 0;
		while (j < game->map->x)
		{
			if (game->map->scene[i][j] == tile)
				draw_rect(&game->screen.map, (t_rect){
					(j * MINI_TILE) + MAPOS, (i * MINI_TILE) + MAPOS,
					MINI_TILE - 1, MINI_TILE - 1, color});
			j++;
		}
		i++;
	}
}

void	setup_minimap(t_game *game)
{
	draw_ray(game->map, &game->screen.map, (t_line){
		game->player->pos_xm, game->player->pos_ym,
		game->player->delta_xm, game->player->delta_ym,
		0.0, WHITE}, 0);
	rays_fov(game, game->player, &game->player->rays);
}

void	render_map_view(t_game *game)
{
	render_background(&game->screen.map,
		chartohex(game->map->colors[0], 0),
		chartohex(game->map->colors[1], 0));
	setup_minimap(game);
	if (game->screen.toggle_minimap == 1)
	{
		render_minimap_tile(game, game->player->skin, WHITE);
		render_minimap_tile(game, FLOOR, WHITE);
		render_minimap_tile(game, WALL, BLACK);
		render_minimap_tile(game, DOOR, 0xcc8e35);
		render_minimap_tile(game, EMPTY_ZONE, 0xccBDC3C7);
		draw_line(&game->screen.map, (t_dline){
			game->player->pos_xm,
			game->player->pos_ym,
			game->player->rays.rx, 
			game->player->rays.ry, 
			0, 0, game->player->rays.color});
		draw_line(&game->screen.map, (t_dline){
				game->player->pos_xm,
				game->player->pos_ym,
				game->player->pos_xm + game->player->delta_xm * 4, 
				game->player->pos_ym + game->player->delta_ym * 4,
				0, 0, RED});
		draw_circle(&game->screen.map, (t_circle){
			game->player->pos_xm,
			game->player->pos_ym,
			MINI_TILE / (SCALE / 1.5), RED});
	}
}

int	render_view(t_game *game)
{
	if (game->is_started == 0)
	{
		start_view(game);
		mlx_put_image_to_window(game->screen.mlx,
			game->screen.win, game->screen.welcome.mlx_img, 0, 0);
		return (game->is_started);
	}
	render_map_view(game);
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->screen.map.mlx_img, 0, 0);
	return (SUCCESS);
}
