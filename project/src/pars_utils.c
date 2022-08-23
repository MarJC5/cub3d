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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (*s1 && *s2)
	{
		while (s1[i] && (s1[i] == s2[i]))
			i++;
		return (s1[i] - s2[i]);
	}
	return (-1);
}

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

void    print_map_details(t_game *game)
{
	int i;

	i = 0;
	ft_printf("\033[0;33mASSETS\033[0m:\n");
	while (i < 4)
		ft_printf("%s", game->map->assets[i++]);
	i = 0;
	ft_printf("\033[0;31mCOLORS\033[0m:\n");
	while (i < 2)
		ft_printf("%s", game->map->colors[i++]);
	ft_printf("\033[0;36mMAP\033[0m:\n%s\n\nSIZE:\nx -> %d \ny -> %d\n",
			  game->map->scene, game->map->x, game->map->y);
}