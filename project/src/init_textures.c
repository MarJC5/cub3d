/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:34:25 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 14:12:32 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_int_texture(t_game *game, int j, int i)
{
	if (ft_strcmp(game->map->identifier[j], "NO") == 0)
		game->text.no = i;
	else if (ft_strcmp(game->map->identifier[j], "EA") == 0)
		game->text.ea = i;
	else if (ft_strcmp(game->map->identifier[j], "SO") == 0)
		game->text.so = i;
	else if (ft_strcmp(game->map->identifier[j], "WE") == 0)
		game->text.we = i;
}

void	init_texture(t_game *game)
{
	int	i;

	i = 0;
	game->text.img = ft_calloc(6, sizeof(void *));
	game->text.img[0] = mlx_xpm_file_to_image(game->screen.mlx,
			game->map->assets[0], &game->text.h, &game->text.w);
	init_int_texture(game, i, 0);
	i++;
	game->text.img[1] = mlx_xpm_file_to_image(game->screen.mlx,
			game->map->assets[1], &game->text.h, &game->text.w);
	init_int_texture(game, i, 1);
	i++;
	game->text.img[2] = mlx_xpm_file_to_image(game->screen.mlx,
			game->map->assets[2], &game->text.h, &game->text.w);
	init_int_texture(game, i, 2);
	i++;
	game->text.img[3] = mlx_xpm_file_to_image(game->screen.mlx,
			game->map->assets[3], &game->text.h, &game->text.w);
	init_int_texture(game, i, 3);
	i++;
	game->text.img[4] = mlx_xpm_file_to_image(game->screen.mlx,
			"./assets/textures/default/xpm/4.xpm",
			&game->text.h, &game->text.w);
	game->player->weapon.has_weapon += 1;
}

void	init_weapon_knife(t_game *game)
{
	game->player->weapon.knife = ft_calloc(5, sizeof(void *));
	game->player->weapon.knife[0] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/knife_0.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.knife[1] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/knife_1.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.knife[2] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/knife_2.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.knife[3] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/knife_1.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.has_weapon += 1;
}

void	init_weapon_pistole(t_game *game)
{
	game->player->weapon.pistol = ft_calloc(5, sizeof(void *));
	game->player->weapon.pistol[0] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/pistol_0.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.pistol[1] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/pistol_1.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.pistol[2] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/pistol_2.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.pistol[3] = mlx_xpm_file_to_image(
			game->screen.mlx, "./assets/weapons/xpm/pistol_1.xpm",
			&game->player->weapon.h, &game->player->weapon.w);
	game->player->weapon.inuse = game->player->weapon.knife[0];
}
