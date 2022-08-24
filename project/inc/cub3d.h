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

# define SUCCESS 0
# define FAILURE 1
# define ERR_PRESET 2
# define ERR_CHAR 3
# define ERR_MAP 4
# define ERR_NAME 5

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
    int     is_valid;
    char    spawn;
	char    *map;
    char    **identifier;
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
int     printinvalid(int errno);
int     printerr(char *err);
int     ft_isspace(char c);
int	    ft_strcmp(char *s1, char *s2);

/**
 * Parsing
 */

int     check_map_textures(char **identifier);
int     check_map_char(char *map);
int     check_map_name(t_game *game, char *file);
void    init_map(t_game *game, char *file);
void    setup_scene_arr(t_game *game);
void    print_map_details(t_game *game);
char    *replace_char(char *str, char find, char replace);

#endif