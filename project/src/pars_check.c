/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:15 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/29 11:12:38 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_map_name(t_game *game, char *file)
{
	if (ft_strcmp(ft_strrchr(file, '.'), ".cub") != 0)
		return (printinvalid(ERR_NAME));
	game->map->fd = open(file, O_RDONLY);
	if (game->map->fd == -1)
		return (FAILURE);
	return (SUCCESS);
}

void	check_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->y && game->player->is_ready == 0)
	{
		j = 0;
		while (j < game->map->x)
		{
			if (game->map->scene[i][j] == 'N'
				|| game->map->scene[i][j] == 'S'
				|| game->map->scene[i][j] == 'E'
				|| game->map->scene[i][j] == 'W')
			{
				game->player->pos_y = ((double)(i * TILE_SIZE))
					+ TILE_SIZE / 2 + MAPOS;
				game->player->pos_x = ((double)(j * TILE_SIZE))
					+ TILE_SIZE / 2 + MAPOS;
				game->player->skin = game->map->scene[i][j];
				game->player->is_ready = 1;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	check_map_char(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_isspace(map[i])
			|| map[i] == '1'
			|| map[i] == '0'
			|| map[i] == 'N'
			|| map[i] == 'S'
			|| map[i] == 'E'
			|| map[i] == 'W'
			|| map[i] == '\n'
			|| map[i] == '\0')
			i++;
		else
			return (ERR_CHAR);
	}
	return (SUCCESS);
}

int	check_map_textures(char **identifier)
{
	if (ft_strcmp(identifier[0], "NO") == 0
		&& ft_strcmp(identifier[1], "SO") == 0
		&& ft_strcmp(identifier[2], "WE") == 0
		&& ft_strcmp(identifier[3], "EA") == 0
		&& ft_strcmp(identifier[4], "F") == 0
		&& ft_strcmp(identifier[5], "C") == 0)
		return (SUCCESS);
	return (ERR_PRESET);
}
