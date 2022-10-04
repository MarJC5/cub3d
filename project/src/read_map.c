/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:28 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 14:41:22 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	whilebn(t_game *game, char **line)
{
	while (*line[0] == '\n')
	{
		free_stuff(*line);
		*line = get_next_line(game->map->fd);
	}
}

int	save_map(t_game *game, char *save, char *line, int y)
{
	save = ft_strdup("");
	game->map->x = (int)ft_strlen(line);
	whilebn(game, &line);
	while (line != NULL)
	{
		if (game->map->map != NULL)
			free_stuff(game->map->map);
		if (game->map->x < (int)ft_strlen(line))
			game->map->x = (int)ft_strlen(line);
		game->map->map = ft_strjoin(save, line);
		free(save);
		save = ft_strdup(game->map->map);
		free(line);
		line = get_next_line(game->map->fd);
		y++;
	}
	free_stuff(save);
	game->map->y = y;
	return (printinvalid(check_map_char(game->map->map)));
}

static int	ligne_gain(int i, int j)
{
	if (i == 3)
		return (0);
	return (j);
}

int	save_map_textures(t_game *game, int i, int j, char *line)
{
	size_t	len;
	int		k;

	k = 0;
	while (++i < 6)
	{
		whilebn(game, &line);
		if (ft_strcmp(line, "\n") != 0 && i < 4)
		{
			len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
			game->map->identifier[k++] = ft_substr(line, 0, len);
			game->map->assets[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
			game->map->assets[j - 1]
			[strlen(game->map->assets[j - 1]) - 1] = '\0';
			j = ligne_gain(i, j);
		}
		if (ft_strcmp(line, "\n") != 0 && i >= 4)
		{
			len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
			game->map->identifier[k++] = ft_substr(line, 0, len);
			game->map->colors[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
		}
		free_stuff(line);
		line = get_next_line(game->map->fd);
	}
	free_stuff(line);
	return (printinvalid(check_map_textures(game->map->identifier)));
}

void	save_map_scene(t_game *game, int i, int j, int k)
{
	if (setup_scene_arr(game) == SUCCESS)
	{
		while (j < game->map->y)
		{
			k = 0;
			while (k < game->map->x)
			{
				if (game->map->map[i] == '\n'
					|| game->map->map[i] == '\0')
				{
					i++;
					break ;
				}
				if (!ft_isspace(game->map->map[i]) && game->map->map[i] != '\n')
					game->map->scene[j][k] = game->map->map[i];
				k++;
				i++;
			}
			j++;
		}
	}
}
