/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 17:44:29 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_map_name(t_game *game, char *file)
{
	if (ft_strcmp(ft_strrchr(file, '.'), ".cub") != 0)
		return (printinvalid(ERR_NAME));
	game->map->fd = open(file, O_RDONLY);
	return (SUCCESS);
}

void	int_player_pos(t_game *game, char location, double x, double y)
{
	if (location == 'N'
		|| location == 'S'
		|| location == 'E'
		|| location == 'w')
	{
		game->player->pos_x = x;
		game->player->pos_y = y;
		ft_printf("\n\033[1;37mPLAYER START POS\033[0m:\nx -> %d &p[%p]\ny -> %d &p[%p]\n",
		game->player->pos_x, game->player->pos_y, game->player->pos_x, game->player->pos_y);
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
			|| map[i] == 'w'
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
