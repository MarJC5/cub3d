/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:36:40 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 17:40:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_fd(t_game *game)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = open(game->map->assets[i], O_RDONLY);
		if (fd == -1)
		{
			close(fd);
			printinvalid(ERR_FD);
			return (FAILURE);
		}
		i++;
		close(fd);
	}
	return (SUCCESS);
}

void	spawn_cheker(t_game *game, int i, int j)
{
	game->player->save += 1;
	game->map->scene[i][j] = '0';
	if (game->player->save > 1)
		printinvalid(ERR_PLAYER);
}

int	free_hex(char **tab)
{
	ft_free_multitab(tab);
	return (FAILURE);
}

int	free_error(t_game *game, char **line, int i)
{
	free(game->map->identifier[5]);
	free(game->map->identifier[4]);
	free_stuff(*line);
	if (i == 0)
		return (printinvalid(ERR_TEXT));
	return (1);
}
