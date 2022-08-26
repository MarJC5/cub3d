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

# define WIN_NAME "cub3D"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define WALL '1'
# define FLOOR '0'
# define EMPTY_ZONE '.'

# define TILE_SIZE 8
# define MAPOS 20

# include "key_macos.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>

/**
 * Struct
 */

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_player
{
	int		is_ready;
	char    skin;
	double	pos_x;
	double	pos_y;
	double	planet_x;
	double	planet_y;
}	t_player;


typedef struct s_screen
{
	void	*mlx;
	void	*win;
	int     toggle_minimap;
	t_img   img;
}	t_screen;

typedef struct s_map
{
	int		fd;
	int		x;
	int		y;
	int     **map2D;
	char	*map;
	char	**identifier;
	char	**colors;
	char	**assets;
	char	**scene;
}	t_map;

typedef struct s_game
{
	double		time;
	double		old_time;
	t_player	*player;
	t_screen	screen;
	t_map		*map;
}	t_game;

/**
 * Init
 */

void	init_screen(t_game *game);
void	init_map_var(t_game *game);
void	init_map(t_game *game, char *file);
void    init_map_preset(t_game *game);
void	init_screen(t_game *game);

/**
 * Utils
 */
int		printinvalid(int errno);
int		printerr(char *err);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
int     encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
int     splitoi(char *tab);
int     fpf_rect(t_img *img, t_rect rect);
void	img_pix_put(t_img *img, int x, int y, int color);

/**
 * Parsing
 */
int		check_map_textures(char **identifier);
int		check_map_char(char *map);
int		check_map_name(t_game *game, char *file);
int		setup_scene_arr(t_game *game);
char	*replace_char(char *str, char find, char replace);
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
int     fill_minimap(t_game *game, char tile, int color);
void	check_player_pos(t_game *game);
void	render_background(t_img *img, int floor, int ceilling);
void    display_minimap(t_game *game);

/**
 * Key events
 */
int		esc_win(t_game *game);
int		key_event(int key, t_game *game);

#endif
