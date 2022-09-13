/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:15 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/13 08:16:42 by jmartin          ###   ########.fr       */
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

float	init_player_angle(char angle)
{
	if (angle == 'N')
		return (0.0);
	if (angle == 'E')
		return (1.5708f);
	if (angle == 'S')
		return (3.14159f);
	if (angle == 'W')
		return (4.71239f);
	return (0);
}

void	check_player_pos(t_game *game, int i, int j)
{
	while (i < game->map->y && game->player->is_ready == 0)
	{
		j = -1;
		while (++j < game->map->x)
		{
			if (game->map->scene[i][j] == 'N' || game->map->scene[i][j] == 'S'
				|| game->map->scene[i][j] == 'E'
				|| game->map->scene[i][j] == 'W')
			{
				game->player->pos_y = i;
				game->player->pos_x = j;
				game->player->pos_ym = (i * MINI_TILE) + MAPOS + (SCALE - 1);
				game->player->pos_xm = (j * MINI_TILE) + MAPOS + (SCALE - 1);
				game->player->skin = game->map->scene[i][j];
				game->player->angle = init_player_angle(game->player->skin);
				game->player->delta_x = cos(game->player->angle) * SPEED;
				game->player->delta_y = sin(game->player->angle) * SPEED;
				game->player->delta_xm = cos(game->player->angle) * (SPEED / 2);
				game->player->delta_ym = sin(game->player->angle) * (SPEED / 2);
				game->player->is_ready = 1;
				break ;
			}
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
			|| map[i] == 'D'
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
	return (SUCCESS);
}
