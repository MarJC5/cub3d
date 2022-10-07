/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:48:21 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 12:32:41 by jmartin          ###   ########.fr       */
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

void	fps(t_game *game)
{
	game->screen.oldtime = game->screen.time;
	current_timestamp(game);
	game->screen.frametime = (game->screen.time - game->screen.oldtime);
}
