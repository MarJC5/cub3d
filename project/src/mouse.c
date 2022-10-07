/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:05:36 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/07 12:56:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	toggle_mouse_visibility(t_game *game)
{
	if (game->screen.toggle_mouse == 0)
	{
		game->screen.toggle_mouse = 1;
		mlx_mouse_hide(game->screen.mlx, game->screen.win);
	}
	else if (game->screen.toggle_mouse == 1)
	{
		game->screen.toggle_mouse = 0;
		mlx_mouse_show();
	}
}

int	mouse_event(int x, int y, t_game *game)
{
	(void) y;
	if (x < game->screen.oldx && x > 0)
	{
		game->screen.oldx = x;
		move_left(game);
	}
	else if (x > game->screen.oldx && x < WIN_WIDTH)
	{
		game->screen.oldx = x;
		move_right(game);
	}
	else
	{
		if (game->screen.toggle_mouse == 1)
		{
			mlx_mouse_move(game->screen.win,
				(WIN_WIDTH / 2), (WIN_HEIGHT / 2));
			game->screen.oldx = WIN_WIDTH / 2;
		}
		else
			game->screen.oldx = x;
	}
	return (x);
}
