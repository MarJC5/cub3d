/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/22 12:23:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    save_map(t_game *game)
{
	char    *save;
	char    *line;
	int     y;

	line = get_next_line(game->map->fd);
	save = ft_strdup("");
	game->map->x = ft_strlen(line);
	y = 0;
	while (line != NULL)
	{
		if (game->map->x < (int)ft_strlen(line))
			game->map->x = (int)ft_strlen(line);
		game->map->map = ft_strjoin(save, line);
		free(save);
		save = ft_strdup(game->map->map);
		free(line);
		line = get_next_line(game->map->fd);
		y++;
	}
	game->map->y = y;
	free(save);
}

void    save_map_textures(t_game *game)
{
	char    *line;
	int     i;
	int     j;

	i = 0;
	j = 0;
	line = get_next_line(game->map->fd);
	while (i < 7)
	{
		if (ft_strcmp(line, "\n") != 0 && i < 4)
		{
			game->map->assets[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
			if (i == 3)
				j = 0;
		}
		if (ft_strcmp(line, "\n") != 0 && i > 4)
			game->map->colors[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
		free(line);
		line = get_next_line(game->map->fd);
		i++;
	}
}

void save_map_scene(t_game *game, int i, int j, int k)
{
    setup_scene_arr(game);
    while (j < game->map->y)
    {
        k = 0;
        while (k < game->map->x)
        {
            if (game->map->map[i + 1] == '\n' || game->map->map[i + 1] == '\0')
            {
                i++;
                k++;
                break;
            }
            if (!ft_isspace(game->map->map[i]) && game->map->map[i] != '\n')
                game->map->scene[j][k] = game->map->map[i];
            k++;
            i++;
        }
        j++;
    }
}

void    init_map(t_game *game, char *file)
{
	if (check_map_name(game, file) == 0)
	{
        save_map_textures(game);
        save_map(game);
        save_map_scene(game, 0, 0, 0);
		print_map_details(game);
	}
}