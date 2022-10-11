/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:28 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 16:47:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	save_map_textures(t_game *game, int i, int j, char *line)
{
	size_t	len;
	int		k;
	int		g;

	k = 0;
	g = 4;
	while (++i < 6)
	{
		whilebn(game, &line);
		if (ft_strcmp(line, "\n") != 0)
		{
			if (ft_strchr(line, ' ') == NULL)
				return (printinvalid(ERR_TEXT));
			len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
			if (len >= 2)
			{
				game->map->identifier[k++] = ft_substr(line, 0, len);
				printf("j : %d\n", j);
				game->map->assets[j++] = ft_strdup(ft_strchr(line, ' ') + 1);
				game->map->assets[j - 1]
				[strlen(game->map->assets[j - 1]) - 1] = '\0';
			}
			else
			{
				game->map->temp = ft_substr(line, 0, len);
				if (game->map->temp[0] == 'F' && g <= 5)
				{
					game->map->identifier[g++] = ft_strdup(game->map->temp);
					game->map->colors[0] = ft_strdup(ft_strchr(line, ' ') + 1);
				}
				else if (game->map->temp[0] == 'C' && g <= 5)
				{
					game->map->identifier[g++] = ft_strdup(game->map->temp);
					game->map->colors[1] = ft_strdup(ft_strchr(line, ' ') + 1);
				}
				free(game->map->temp);
			}
		}
		free_new_read(game, &line, i);
	}
	return (printinvalid(check_map_textures(game->map->identifier, 0)));
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
