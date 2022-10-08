/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:37 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/08 09:58:40 by jmartin          ###   ########.fr       */
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
		while (i--)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
}

void	ft_free_multitab_void(void **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
			i++;
		while (i--)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
}

void	free_map(t_game *game)
{
	ft_free_multitab_void(game->text.img);
	ft_free_multitab_void(game->player->weapon.knife);
	ft_free_multitab_void(game->player->weapon.pistol);
	ft_free_multitab(game->map->assets);
	ft_free_multitab(game->map->colors);
	ft_free_multitab(game->map->identifier);
	ft_free_multitab(game->map->scene);
	close(game->map->fd);
	free(game->map->map);
	free(game->map);
	free(game->player);
}

void	sound_kill(void)
{
	const char	*command;

	command = "pkill afplay";
	system(command);
}
