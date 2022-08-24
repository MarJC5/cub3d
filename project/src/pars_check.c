/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/22 12:23:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_map_name(t_game *game, char *file)
{
    if (ft_strcmp(ft_strrchr(file, '.'), ".cub") != 0)
        return (printinvalid(ERR_NAME));
    game->map = malloc(sizeof(t_map));
    game->map->fd = open(file, O_RDONLY);
    game->map->colors = malloc( (2 * sizeof(char *)) + 1);
    game->map->assets = malloc( (4 * sizeof(char *)) + 1);
    game->map->identifier = malloc( (6 * sizeof(char *)) + 1);
    return (SUCCESS);
}

int	check_map_char(char *map)
{
    int i;

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

int check_map_textures(char **identifier)
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

