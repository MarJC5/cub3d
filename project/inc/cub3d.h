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
# define WRONG_PLAY "Wrong SPAWNER POSTION in map."
# define WRONG_PRESET "Wrong identifier."
# define WRONG_MAP "Map is not enclosed by 1."
# define WRONG_FILE "Wrong asset path"
# define WRONG_NAME "Wrong map name, please give a *.cub file"
# define MAP_UNCLOSED "The map is not closed by the char '1'"
# define MAP_CHAR "The texture/color of the map is false"

# define SUCCESS 0
# define FAILURE 1

# define ERR_PRESET 2
# define ERR_CHAR 3
# define ERR_MAP 4
# define ERR_NAME 5
# define ERR_UNCLOSED 6
# define ERR_TEXT 7
# define ERR_PLAYER 8
# define ERR_FD 9

# define ORANGE 0xfeca57
# define FRONT_WALL 0x43424a
# define SIDE_WALL 0x1f1e23

# define WHITE 0xffffff
# define BLACK 0x1f1e23
# define GREY 0x8b8b8b
# define BROWN 0x73493c
# define RED 0x871a1a
# define YELLOW 0xdcac6c
# define GREEN 0x6a9254
# define BLUE 0x524ba3

# define WIN_NAME "cub3D"
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# define FRAME_TIME 50.0

# define SOUND_CUT 0
# define SOUND_SHOT 1
# define SOUND_THEME 2
# define SOUND_DOOR 3
# define SOUND_MENU 4
# define SOUND_ON 0

# define WALL '1'
# define FLOOR '0'
# define EMPTY_ZONE '.'
# define DOOR 'D'
# define DOOR_OPEN '3'

# define SPEED 5
# define SPEED_MOUSE 25
# define SCALE 4
# define SPRITE_SIZE 64
# define TILE_SIZE 32
# define MINI_TILE 8
# define MAPOS 8
# define FOV 60
# define COLLISION 3

# define DR 0.0174533
# define PI 3.1415926535

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
# include <sys/time.h>
# include <fcntl.h>

/**
 * Struct
 */

typedef struct s_pars_map
{
	char	*line;
	int		i;
	int		j;
	int		k;
	size_t	len;
}	t_pars_map;

typedef struct s_art
{
	int		x;
	int		y;
	int		fd;
	int		posx;
	int		posy;
	float	size;
	int		color;
	char	*file;
	char	*tmp;
	char	*save;
	char	*line;
	char	*tab;
	char	**tab_art;
	void	*mlx_img;
}	t_art;

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

typedef struct s_dline
{
	double	begin_x;
	double	begin_y;
	double	end_x;
	double	end_y;
	double	delta_x;
	double	delta_y;
	int		color;
}	t_dline;

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
	int		r;
	int		color;
	int		doorh;
	int		doorv;
	int		door;
	float	posx;
	float	posy;
	float	deltax;
	float	deltay;
	float	dist;
	float	angle;
	float	wall_height;
	float	wall_offset;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		hshift;
	int		vshift;
	float	hmrx;
	float	hmry;
	float	vmrx;
	float	vmry;
	float	rx;
	float	ry;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	ra;
	float	xo;
	float	yo;
	float	dis_h;
	float	dis_v;
	float	atan;
	float	ntan;
	int		text;
	int		oldy;
	int		oldx;
	int		voldy;
	int		voldx;
	int		rettest;
}	t_rays;

typedef struct s_weapon
{
	void	**knife;
	void	**pistol;
	void	*inuse;
	int		current;
	int		has_weapon;
	int		frame;
	int		h;
	int		w;
}	t_weapon;

typedef struct s_player
{
	int			is_ready;
	int			pos;
	int			save;
	char		skin;
	float		dir;
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
	t_weapon	weapon;
}	t_player;

typedef struct s_screen
{
	void		*mlx;
	void		*win;
	int			toggle_minimap;
	int			toggle_audio;
	int			toggle_mouse;
	int			toggle_weapon;
	int			oldx;
	double		time;
	double		oldtime;
	double		frametime;
	t_img		welcome;
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
	char	*temp;
	char	*map;
	char	**identifier;
	char	**colors;
	char	**assets;
	char	**scene;
	t_img	img;
}	t_map;

typedef struct s_col
{
	int	x;
	int	y;
	int	px;
	int	py;
}	t_col;

typedef struct s_text
{
	void	**img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		h;
	int		w;
	int		x;
	int		y;
	int		y2;
	int		pixel;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		count;
}	t_text;

typedef struct s_game
{
	int			is_started;
	int			s;
	int			c;
	int			k;
	t_screen	screen;
	t_player	*player;
	t_map		*map;
	t_text		text;
	t_col		col;
}	t_game;

/**
 * @brief
 * Init
 */

void	init_ascii(t_art art);
void	init_screen(t_game *game);
void	init_view(t_game *game);
void	init_default(t_game *game);
void	spawn_cheker(t_game *game, int i, int j);
int		init_map(t_game *game, char *file);
int		check_fd(t_game *game);

/**
 * @brief
 * Parsing
 */
int		free_hex(char **tab);
int		free_error(t_game *game, char **line, int i);
int		printerr(char *err);
int		setup_scene_arr(t_game *game);
int		check_map_textures(char **identifier, int i, char *j);
int		check_map_char(char *map);
int		check_map_name(t_game *game, char *file);
int		save_map(t_game *game, char *save, char *line, int y);
int		save_map_textures(t_game *game, int i, int j, char *line);
int		ligne_gain(int i, int j);

void	free_new_read(t_game *game, char **line, int i);
void	save_map_scene(t_game *game, int i, int j, int k);
void	print_map_details(t_game *game);
void	whilebn(t_game *game, char **line);

char	*replace_char(char *str, char find, char replace);

/**
 * @brief
 * Events
 */

int		mouse_event(int x, int y, t_game *game);
int		key_event(int key, t_game *game);
int		esc_win(t_game *game);

void	toggle_weapon(t_game *game);
void	toggle_audio(t_game *game);
void	toggle_mouse_visibility(t_game *game);
void	open_door(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_fleft(t_game *game);
void	move_fright(t_game *game);

/**
 * @brief
 * Utils
 */

int		printinvalid(int errno);
int		ft_isspace(char c);
int		ft_strcmp(char *s1, char *s2);
int		encode_rgb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
int		chartohex(char *tab, int opacity);
int		fixang(int ang);

float	radtodeg(float ang);
float	degtorad(float ang);
float	dist(t_player *player, t_rays *rays);

void	reset_angle(t_rays *ray);
int		ret_doublon(char *j, int count);

/**
 * @brief
 * Screen
 */
int		render_welcome(t_game *game);
int		render_view(t_game *game);

void	rays_fov(t_game *game, t_player *player, t_rays *ray);
void	draw_rect(t_img *img, t_rect rect);
void	draw_circle(t_img *img, t_circle circle);
void	draw_line(t_img *img, t_dline line);
void	draw_floor(t_game *game, t_rays *ray, int r);
void	draw_ceiling(t_game *game, t_rays *ray, int r);
void	draw_wall(t_game *game, t_rays *ray, int r);
void	render_minimap(t_game *game);
void	render_background(t_img *img, int floor, int ceilling);
void	img_pix_put(t_img *img, int x, int y, int color);
void	check_player_pos(t_game *game, int i, int j);
void	render_stat(t_game *game, int x, int y, int data);
void	start_view(t_game *game);
int		init_orientation(t_game *game, t_rays *ray);
int		init_orientation_v(t_game *game, t_rays *ray);

float	draw_ray(t_map *map, t_img *img, t_line line, int active);

/**
 * @brief
 * Free
 */
void	free_map(t_game *game);
void	ft_free_multitab(char **tab);
void	ft_free_multitab_void(void **tab);
void	free_stuff(char *tofree);

/**
 * @brief
 * Map
 */
int		check_map(t_game *game);

void	draw_board(t_img *img);

/**
 * @brief
 * Collision
 */
int		collision(t_game *game);
int		collision_bck(t_game *game);
int		collision_right(t_game *game);
int		collision_left(t_game *game);

/**
 * @brief
 * RAY
 */
void	fix_fisheye(t_game *game, t_rays *ray);
void	verti_loop( t_map *map, t_player *player, t_rays *rays);
void	hori_loop(t_map *map, t_player *player, t_rays *rays);
double	time_now(void);

void	fps(t_game *game);
void	print_fps(t_game *game);
void	current_timestamp(t_game *game);
void	init_tile(char *path, int x, int y, t_game *game);
void	init_int_texture(t_game *game, int j, int i);
void	init_texture(t_game *game);
void	init_weapon_knife(t_game *game);
void	init_weapon_pistole(t_game *game);

int		weapon_action(t_game *game, int i);
int		weapon_change(t_game *game);
int		weapon_use(t_game *game);

void	print_info(t_game *game);
/**
 * @brief
 * Audio
 */
void	play_sounds(t_game *game, int sound_id);
void	sound_kill(void);
void	menu_sound(void);

#endif
