/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:48:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/05 07:33:44 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	time_now(void)
{
	struct timeval	tv;
	double			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
	return (time);
}

void	current_timestamp(t_game *game)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	game->screen.time = (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

void	print_fps(t_game *game)
{
	double	frame;
	char	*fps;

	frame = 1.0 / game->screen.frametime;
	fps = ft_itoa(frame);
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + MINI_TILE), 20, YELLOW, "fps: ");
	mlx_string_put(game->screen.mlx, game->screen.win,
		((game->map->x * MINI_TILE) + 40), 20, YELLOW, fps);
	free(fps);
}

void	fps(t_game *game)
{
	game->screen.oldtime = game->screen.time;
	current_timestamp(game);
	game->screen.frametime = (game->screen.time - game->screen.oldtime);
}
