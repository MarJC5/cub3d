/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:44:12 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 12:34:09 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	sound_info(t_game *game)
{	
	if (game->screen.toggle_audio == 0)
	{
		mlx_string_put(game->screen.mlx, game->screen.win,
			((game->map->x * MINI_TILE) + MINI_TILE),
			20, YELLOW, "sound: off");
	}
	else if (game->screen.toggle_audio == 1)
	{
		mlx_string_put(game->screen.mlx, game->screen.win,
			((game->map->x * MINI_TILE) + MINI_TILE),
			20, YELLOW, "sound: on");
	}
}

static void	mouse_info(t_game *game)
{
	if (game->screen.toggle_mouse == 0)
	{
		mlx_string_put(game->screen.mlx, game->screen.win,
			((game->map->x * MINI_TILE) + MINI_TILE),
			40, YELLOW, "mouse: on");
	}
	else if (game->screen.toggle_mouse == 1)
	{
		mlx_string_put(game->screen.mlx, game->screen.win,
			((game->map->x * MINI_TILE) + MINI_TILE),
			40, YELLOW, "mouse: off");
	}
}

void	print_fps(t_game *game)
{
	double	frame;
	char	*fps;

	frame = 1.0 / game->screen.frametime;
	fps = ft_itoa(frame);
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + MINI_TILE), 60, YELLOW, "fps: ");
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + 40), 60, YELLOW, fps);
	free(fps);
}

static void	pos_info(t_game *game)
{
	char	*pos;

	pos = ft_itoa((int)game->player->pos_x);
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + MINI_TILE), 80, YELLOW, "x: ");
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE + 20) + MINI_TILE), 80, YELLOW, pos);
	free(pos);
	pos = ft_itoa((int)game->player->pos_y);
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + MINI_TILE), 100, YELLOW, "y: ");
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE + 20) + MINI_TILE), 100, YELLOW, pos);
	free(pos);
}

void	print_info(t_game *game)
{
	print_fps(game);
	pos_info(game);
	sound_info(game);
	mouse_info(game);
}
