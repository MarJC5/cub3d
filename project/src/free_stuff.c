/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/22 12:23:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    free_stuff(char *tofree)
{
	if (tofree)
		free(tofree);
}

void    free_map(t_game *game)
{
	int i;

	i = 2;
	while (game->map->colors[i])
		free_stuff(game->map->colors[i--]);
	i = 4;
	while (game->map->assets[i])
		free_stuff(game->map->assets[i--]);
	i = 6;
	while (game->map->identifier[i])
		free_stuff(game->map->identifier[i--]);
	while (game->map->y)
	{
		while (game->map->x)
			free_stuff(game->map->scene[game->map->x--]);
		free_stuff(game->map->scene[game->map->y--]);
	}
	free(game->map);
}