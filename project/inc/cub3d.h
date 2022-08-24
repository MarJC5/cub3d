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

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# include <stdlib.h>

/**
 * Struct
 */

typedef struct map
{
	int     fd;
	int     x;
	int     y;
	char    *map;
	char    **colors;
	char    **assets;
    char    **scene;
} t_map;

typedef struct game
{
	t_map		*map;
} t_game;

/**
 * Utils
 */
int     printerr(char *err);
int     ft_isspace(char c);
int	    ft_strcmp(char *s1, char *s2);

/**
 * Parsing
 */

int     check_map_name(t_game *game, char *file);
void    init_map(t_game *game, char *file);
void    setup_scene_arr(t_game *game);
void    print_map_details(t_game *game);
char    *replace_char(char *str, char find, char replace);

#endif