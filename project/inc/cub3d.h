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
# define MAP_UNCLOSED "The map is not closed by the char '1'"

# define SUCCESS 0
# define FAILURE 1

# define ERR_PRESET 2
# define ERR_CHAR 3
# define ERR_MAP 4
# define ERR_NAME 5
# define ERR_UNCLOSED 6

# define WIN_NAME "cub3D"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define WALL '1'
# define FLOOR '0'
# define EMPTY_ZONE '.'

# define SPEED 5
# define SCALE 4
# define TILE_SIZE 64
# define MINI_TILE 8
# define MAPOS 8
# define FOV 60
# define COLLISION 0.7f

# define DR 0.0174533

# include "key_macos.h"
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
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
	int	width;
	int	height;
	int	color;
}	t_rect;

typedef struct s_circle
{
	int	x;
	int	y;
	int	radius;
	int	color;
}	t_circle;

typedef struct s_line
{
	float	posx;
	float	posy;
	float	delta_x;
	float	delta_y;
	float	dist;
	int		color;
}	t_line;

typedef struct s_rays
{
	float	posx;
	float	posy;
	float	deltax;
	float	deltay;
	float	dist;
	float	angle;
}	t_rays;

typedef struct s_player
{
	int			is_ready;
	int			pos;
	char		skin;
	float		angle;
	float		pos_x;
	float		pos_y;
	float		pos_xm;
	float		pos_ym;
	float		delta_x;
	float		delta_y;
	float		delta_xm;
	float		delta_ym;
	t_rays		rays;
}	t_player;

typedef struct s_screen
{
	void		*mlx;
	void		*win;
	int			toggle_minimap;
	t_img		map;
}	t_screen;

typedef struct s_map
{
	int		fd;
	int		x;
	int		y;
	int		size;
	int		map_x;
	int		map_y;
	char	*map;
	char	**identifier;
	char	**colors;
	char	**assets;
	char	**scene;
	t_img	img;
}	t_map;

typedef struct s_game
{
	t_screen	screen;
	t_player	*player;
	t_map		*map;
}	t_game;

/**
 * @brief
 * Init
 */

void	init_screen(t_game *game);
void	init_view(t_game *game);
void	init_default(t_game *game);
int		init_map(t_game *game, char *file);

/**
 * @brief
 * Parsing
 */

int		setup_scene_arr(t_game *game);
int		check_map_textures(char **identifier);
int		check_map_char(char *map);
int		check_map_name(t_game *game, char *file);
int		save_map(t_game *game, char *save, char *line, int y);
int		save_map_textures(t_game *game, int i, int j, char *line);

void	save_map_scene(t_game *game, int i, int j, int k);
void	print_map_details(t_game *game);

char	*replace_char(char *str, char find, char replace);

/**
 * @brief
 * Events
 */

int		key_event(int key, t_game *game);
int		esc_win(t_game *game);

void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);

/**
 * @brief
 * Utils
 */

int		printinvalid(int errno);
int		printerr(char *err);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
int		encode_rgb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
int		chartohex(char *tab, int opacity);
int		fixang(int ang);

float	degtorad(float ang);

/**
 * @brief
 * Screen
 */

int		render_view(t_game *game);

void	rays_fov(t_game *game, t_player *player, t_rays *ray);
void	draw_rect(t_img *img, t_rect rect);
void	draw_circle(t_img *img, t_circle circle);
void	render_minimap(t_game *game);
void	render_minimap_tile(t_game *game, char tile, int color);
void	render_background(t_img *img, int floor, int ceilling);
void	img_pix_put(t_img *img, int x, int y, int color);
void	check_player_pos(t_game *game, int i, int j);
void	render_stat(t_game *game, int x, int y, int data);
void	draw_line(t_img *img, t_line line);

float	draw_ray(t_map *map, t_img *img, t_line line);

/**
 * @brief
 * Free
 */
void	free_map(t_game *game);
void	ft_free_multitab(char **tab);
void	free_stuff(char *tofree);

/**
 * @brief
 * Map
 */
int		check_map(t_game *game);

#endif
