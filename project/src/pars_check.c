/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:15 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 21:09:39 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_map_name(t_game *game, char *file)
{
	if (ft_strrchr(file, '.') == NULL)
		return (printinvalid(ERR_NAME));
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
		return (degtorad(270.1));
	if (angle == 'E')
		return (degtorad(360.1));
	if (angle == 'S')
		return (degtorad(90.1));
	if (angle == 'W')
		return (degtorad(180.1));
	return (0);
}

void	check_player_pos(t_game *game, int i, int j)
{
	while (++i < game->map->y)
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
				spawn_cheker(game, i, j);
			}
		}
	}
	if (game->player->save == 0)
		printinvalid(ERR_PLAYER);
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

int	check_map_textures(char **identifier, int i, char *j)
{
	j = ft_calloc(6, sizeof(char));
	while (i < 6)
		j[i++] = '0';
	i = -1;
	while (identifier[++i])
	{
		if (ft_strcmp(identifier[i], "NO") == 0)
			j[0]++;
		else if (ft_strcmp(identifier[i], "SO") == 0)
			j[1]++;
		else if (ft_strcmp(identifier[i], "WE") == 0)
			j[2]++;
		else if (ft_strcmp(identifier[i], "EA") == 0)
			j[3]++;
		else if (ft_strcmp(identifier[i], "F") == 0)
			j[4]++;
		else if (ft_strcmp(identifier[i], "C") == 0)
			j[5]++;
		else
		{
			free_stuff(j);
			return (ERR_PRESET);
		}
	}
	return (ret_doublon(j, 6));
}
