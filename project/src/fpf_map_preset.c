/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 09:19:28 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)pixel = color;
}

int fpf_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	fpf_render(t_game *game)
{
	render_background(&game->screen.img,
		chartohex(game->map->colors[0], 255),
		chartohex(game->map->colors[1], 255));
	display_minimap(game);
	fpf_rect(&game->screen.img, (t_rect){
		(game->player->pos_x / 2.5) * MAPOS + MAPOS,
		(game->player->pos_y / 2.5) * MAPOS + MAPOS,
		TILE_SIZE, TILE_SIZE, chartohex(game->map->colors[1], 255)});
	mlx_put_image_to_window(game->screen.mlx,
		game->screen.win, game->screen.img.mlx_img, 0, 0);
	return (0);
}

void    init_map_preset(t_game *game)
{
	game->screen.img.mlx_img = mlx_new_image(game->screen.mlx, WIN_WIDTH, WIN_HEIGHT);
	game->screen.img.addr = mlx_get_data_addr(game->screen.img.mlx_img, &game->screen.img.bpp,
	                                          &game->screen.img.line_len, &game->screen.img.endian);
	mlx_loop_hook(game->screen.mlx, &fpf_render, game);
}
