/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 13:42:49 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*replace_char(char *str, char find, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == find)
			str[i] = replace;
		i++;
	}
	return (str);
}

int	setup_scene_arr(t_game *game)
{
	int		i;

	i = 0;
	game->map->scene = ft_calloc(game->map->y + 1, sizeof(char *));
	if (!game->map->scene)
		return (FAILURE);
	game->map->scene[game->map->y] = NULL;
	while (i < game->map->y)
	{
		game->map->scene[i] = ft_calloc(game->map->x, sizeof(char));
		if (!game->map->scene[i])
			return (FAILURE);
		ft_memset(game->map->scene[i], EMPTY_ZONE, game->map->x);
		game->map->scene[i][game->map->x - 1] = '\0';
		i++;
	}
	return (SUCCESS);
}

void	print_map_details(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("\n\033[1;33mASSETS\033[0m:\n");
	while (i < 4)
		ft_printf("%s", game->map->assets[i++]);
	i = 0;
	ft_printf("\n\033[1;31mCOLORS\033[0m:\n");
	while (i < 2)
		ft_printf("%s", game->map->colors[i++]);
	ft_printf("\n\033[1mSIZE\033[0m:\nx -> %d \ny -> %d\n",
		game->map->x, game->map->y);
	i = -1;
	ft_printf("\n\033[1;34mMAPS\033[0m:\n");
	while (++i < game->map->y)
		ft_printf("%s\n", game->map->scene[i]);
}
