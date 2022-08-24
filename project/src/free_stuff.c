/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/24 20:02:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_stuff(char *tofree)
{
	if (tofree)
		free(tofree);
}

void	free_map(t_game *game)
{
	while (game->map->y)
		free_stuff(game->map->scene[game->map->y--]);
	if (game->map->scene)
		free(game->map->scene);
	free_stuff(game->map->map);
	close(game->map->fd);
	free(game->map);
}
