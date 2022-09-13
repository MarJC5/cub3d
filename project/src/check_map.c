/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:47:51 by tpaquier          #+#    #+#             */
/*   Updated: 2022/09/13 08:14:17 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	checker(t_game *game, int i, int j)
{
	if (game->map->scene[i][j] != '0' && game->map->scene[i][j] != '1'
		&& game->map->scene[i][j] != 'N'
		&& game->map->scene[i][j] != 'S'
		&& game->map->scene[i][j] != 'E'
		&& game->map->scene[i][j] != 'W'
		&& game->map->scene[i][j] != 'D')
		return (FAILURE);
	return (SUCCESS);
}

static int	check_zero(t_game *game, int i, int j)
{
	if ((i - 1) >= 0 && (i + 1) < game->map->y && (j - 1) >= 0
		&& (j + 1) < game->map->x)
	{
		if (checker(game, (i - 1), j) == FAILURE)
			return (FAILURE);
		if (checker(game, (i + 1), j) == FAILURE)
			return (FAILURE);
		if (checker(game, i, (j - 1)) == FAILURE)
			return (FAILURE);
		if (checker(game, i, (j + 1)) == FAILURE)
			return (FAILURE);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	check_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->y)
	{
		j = 0;
		while (j < game->map->x)
		{
			if (game->map->scene[i][j] == '0')
			{
				if (check_zero(game, i, j) == FAILURE)
					return (ERR_UNCLOSED);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
