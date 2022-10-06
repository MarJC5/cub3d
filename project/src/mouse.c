/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:05:36 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 15:24:20 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	mouse_event(int x, int y, t_game *game)
{
	(void) y;
	mlx_mouse_hide();
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
		mlx_mouse_move(game->screen.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		game->screen.oldx = WIN_WIDTH / 2;
	}
	return (x);
}
