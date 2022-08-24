/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
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
	{
		printerr("Wrong map name, please give a *.cub file");
		return (EXIT_FAILURE);
	}
	game->map = malloc(sizeof(t_map));
	game->map->fd = open(file, O_RDONLY);
	game->map->colors = malloc( (2 * sizeof(char *)) + 1);
	game->map->assets = malloc( (4 * sizeof(char *)) + 1);
	return (EXIT_SUCCESS);
}

char    *replace_char(char *str, char find, char replace)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == find)
			str[i] = replace;
		i++;
	}
	return (str);
}

void setup_scene_arr(t_game *game)
{
    int i;

    i = 0;
    game->map->scene = malloc((game->map->y * sizeof(char *)));
    game->map->scene[game->map->y] = NULL;
    while (i < game->map->y)
    {
        game->map->scene[i] = malloc((game->map->x * sizeof(char)));
        game->map->scene[i][game->map->x] = '\0';
        ft_memset(game->map->scene[i] , '1', game->map->x);
        i++;
    }
}

void    print_map_details(t_game *game)
{
	int i;

	i = 0;
	ft_printf("\n\033[1;33mASSETS\033[0m:\n");
	while (i < 4)
		ft_printf("%s", game->map->assets[i++]);
	i = 0;
	ft_printf("\n\033[1;31mCOLORS\033[0m:\n");
	while (i < 2)
		ft_printf("%s", game->map->colors[i++]);
    ft_printf("\n\033[1mSIZE\033[0m:\nx -> %d \ny -> %d\n", game->map->x, game->map->y);
    i = 0;
    ft_printf("\n\033[1;34mMAPS\033[0m:\n");
    while (i < game->map->y)
        ft_printf("%s\n", game->map->scene[i++]);
}