/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/05 09:42:12 by jmartin          ###   ########.fr       */
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

void	render_info(t_game *game)
{
	char	*value;
	char	*tmp;

	value = ft_itoa(game->player->pos_x);
	tmp = ft_strjoin("X: ", value);
	mlx_string_put(game->screen.mlx, game->screen.win,
		MAPOS, game->map->y * (MINI_TILE * 1.25), 0x000, tmp);
	free(value);
	free(tmp);
	value = ft_itoa(game->player->pos_y);
	tmp = ft_strjoin("Y: ", value);
	mlx_string_put(game->screen.mlx, game->screen.win,
		MAPOS, game->map->y * (MINI_TILE * 1.4), 0x000, tmp);
	free(value);
	free(tmp);
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

void	render_minimap(t_game *game)
{
	if (game->screen.toggle_minimap == 1)
	{
		render_minimap_tile(game, game->player->skin, 0x33FFFFFF);
		render_minimap_tile(game, FLOOR, 0x33FFFFFF);
		render_minimap_tile(game, WALL, 0x000000);
		render_minimap_tile(game, EMPTY_ZONE, 0xBDC3C7);
		init_ray(game->map, &game->screen,
			game->player, &game->player->rays);
		draw_circle(&game->screen.map, (t_circle){
			game->player->pos_xm,
			game->player->pos_ym,
			MINI_TILE / (SCALE / 1.5), 0xC0392B});
		render_info(game);
	}
}

int	render_view(t_game *game)
{
	render_background(&game->screen.map,
		chartohex(game->map->colors[0], 0),
		chartohex(game->map->colors[1], 0));
	render_minimap(game);
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->screen.map.mlx_img, 0, 0);
	return (0);
}
