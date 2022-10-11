/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:28 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 15:05:15 by jmartin          ###   ########.fr       */
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

static void	save_textures_check_color(t_game *game, int g, int len, char *line)
{
	game->map->temp = ft_substr(line, 0, len);
	if (game->map->temp[0] == 'F' && g <= 5)
	{
		game->map->identifier[g] = ft_strdup(game->map->temp);
		game->map->colors[0] = ft_strdup(ft_strchr(line, ' ') + 1);
		game->c = chartohex(game->map->colors[0], 0);
	}
	else if (game->map->temp[0] == 'C' && g <= 5)
	{
		game->map->identifier[g] = ft_strdup(game->map->temp);
		game->map->colors[1] = ft_strdup(ft_strchr(line, ' ') + 1);
		game->c = chartohex(game->map->colors[1], 0);
	}
	free(game->map->temp);
}

static int	save_textures_check_img(t_game *game, char *line, int j)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i])
		i++;
	if (i > 2)
		return (1);
	game->map->assets[j] = ft_strdup(ft_strchr(line, ' ') + 1);
	game->map->assets[j]
	[ft_strlen(game->map->assets[j]) - 1] = '\0';
	return (0);
}

int	save_map_textures(t_game *game, int i, int j, char *line)
{
	size_t	len;
	int		k;
	int		g;

	k = 0;
	g = 3;
	while (++i < 6)
	{
		whilebn(game, &line);
		if (ft_strcmp(line, "\n") != 0)
		{
			if (ft_strchr(line, ' ') == NULL || game->s == 1 || game->c == 1)
				return (printinvalid(ERR_TEXT));
			len = ft_strlen(line) - ft_strlen(ft_strchr(line, ' '));
			if (len >= 2)
			{
				game->map->identifier[k++] = ft_substr(line, 0, len);
				game->s = save_textures_check_img(game, line, ++j);
			}
			else
				save_textures_check_color(game, ++g, len, line);
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
