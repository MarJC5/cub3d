/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/25 13:54:35 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_stuff(char *tofree)
{
	if (tofree)
	{
		free(tofree);
		tofree = NULL;
	}
}

void	ft_free_multitab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
			i++;
		while (i >= 0)
			free(tab[i--]);
		free(tab);
		tab = NULL;
	}
}

void	free_map(t_game *game)
{
	ft_free_multitab(game->map->assets);
	ft_free_multitab(game->map->colors);
	ft_free_multitab(game->map->identifier);
	ft_free_multitab(game->map->scene);
	free(game->map->map);
	free(game->map);
}
