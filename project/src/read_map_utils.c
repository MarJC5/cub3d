/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:01:48 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 12:23:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	whilebn(t_game *game, char **line)
{
	while (*line[0] == '\n')
	{
		free_stuff(*line);
		*line = get_next_line(game->map->fd);
	}
}

int	ligne_gain(int i, int j)
{
	if (i == 3)
		return (0);
	return (j);
}

void	free_new_read(t_game *game, char **line)
{
	free_stuff(*line);
	*line = get_next_line(game->map->fd);
}
