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

int    save_map(t_game *game, char *save, char *line, int y)
{
	line = get_next_line(game->map->fd);
	save = ft_strdup("");
	game->map->x = ft_strlen(line);
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
    return (printinvalid(check_map_char(game->map->map)));
}

int    save_map_textures(t_game *game, int i, int j, char *line)
{
    size_t len;
    int k;

    k = 0;
	line = get_next_line(game->map->fd);
	while (++i < 7)
	{
		if (ft_strcmp(line, "\n") != 0 && i < 4)
		{
            len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
            game->map->identifier[k++] = ft_substr(line, 0, len);
			game->map->assets[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
			if (i == 3)
				j = 0;
		}
		if (ft_strcmp(line, "\n") != 0 && i > 4)
        {
            len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
            game->map->identifier[k++] = ft_substr(line, 0, len);
            game->map->colors[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
        }
		free(line);
		line = get_next_line(game->map->fd);
	}
    return (printinvalid(check_map_textures(game->map->identifier)));
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
	if (check_map_name(game, file) == SUCCESS)
	{
        if (save_map_textures(game, -1, 0, NULL) == SUCCESS)
        {
            if (save_map(game, NULL, NULL, 0) == SUCCESS)
            {
                save_map_scene(game, 0, 0, 0);
                print_map_details(game);
            }
        }
	}
}