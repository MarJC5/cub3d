/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:23 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 13:45:07 by jmartin          ###   ########.fr       */
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
	game->map->scene = ft_calloc(game->map->y, sizeof(char *));
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
	game->map->size = game->map->y * game->map->x;
	return (SUCCESS);
}

void	print_map_details(t_game *game)
{
	int	i;

	i = 0;
	ft_printf("\n\033[1;37mPLAYER START POS\033[0m:\nx -> %d\ny -> %d\nd° -> %d\n",
		(int)game->player->pos_x, (int)game->player->pos_y,
		(int)radtodeg(game->player->angle));
	ft_printf("\n\033[1;33mASSETS\033[0;37m:\n");
	while (i < 4)
		ft_printf("%s\n", game->map->assets[i++]);
	i = 0;
	ft_printf("\n\033[1;31mCOLORS\033[0;37m:\n");
	while (i < 2)
		ft_printf("%s", game->map->colors[i++]);
	ft_printf("\n\033[1;35mSIZE\033[0;37m:\nx -> %d \ny -> %d\nSize: %d\n",
		game->map->x, game->map->y, game->map->size);
	i = -1;
	ft_printf("\n\033[1;34mMAPS\033[0;37m:\n");
	while (++i < game->map->y)
		ft_printf("%s\n", game->map->scene[i]);
}
