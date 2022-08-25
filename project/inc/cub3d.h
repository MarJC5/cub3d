/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:33:42 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/22 11:36:01 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ERROR "Error"
# define WRONG_CHAR "Wrong characters in map."
# define WRONG_PRESET "Wrong identifier."
# define WRONG_MAP "Map is not enclosed by 1."
# define WRONG_NAME "Wrong map name, please give a *.cub file"

# define EMPTY_ZONE '.'

# define SUCCESS 0
# define FAILURE 1

# define ERR_PRESET 2
# define ERR_CHAR 3
# define ERR_MAP 4
# define ERR_NAME 5

# define WIN_NAME "cub3D"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# include "key_macos.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include "../mlx/mlx.h"
# include "../mlx-linux/mlx.h"

# include <stdlib.h>

/**
 * Struct
 */

typedef struct screen
{
	void	*mlx;
	void	*win;
}	t_screen;


typedef struct map
{
	int		fd;
	int		x;
	int		y;
	char	*map;
	char	**identifier;
	char	**colors;
	char	**assets;
	char	**scene;
}	t_map;

typedef struct game
{
	t_screen	*screen;
	t_map		*map;
}	t_game;

/**
 * Init
 */

void	init_screen(t_game *game);
void	init_map_var(t_game *game);

/**
 * Utils
 */
int		printinvalid(int errno);
int		printerr(char *err);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);

/**
 * Parsing
 */
int		check_map_textures(char **identifier);
int		check_map_char(char *map);
int		check_map_name(t_game *game, char *file);
int		setup_scene_arr(t_game *game);
char	*replace_char(char *str, char find, char replace);
void	init_map(t_game *game, char *file);
void	print_map_details(t_game *game);

/**
 * Free
 */
void	free_map(t_game *game);
void	ft_free_multitab(char **tab);
void	free_stuff(char *tofree);

/**
 * Screen
 */
void	init_screen(t_game *game);

/**
 * Key events
 */
int		esc_win(t_game *game);
int		key_event(int key, t_game *game);

#endif
