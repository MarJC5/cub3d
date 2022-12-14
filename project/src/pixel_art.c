/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:52:57 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 07:42:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	bit_color(int ref)
{
	if (ref == '0')
		return (WHITE);
	if (ref == '1')
		return (BLACK);
	if (ref == '2')
		return (GREY);
	if (ref == '3')
		return (BROWN);
	if (ref == '4')
		return (RED);
	if (ref == '5')
		return (YELLOW);
	if (ref == '7')
		return (GREEN);
	return (BLACK);
}

static void	render_art(t_art art)
{
	int	i;
	int	j;

	i = 0;
	while (i < art.y)
	{
		j = 0;
		while (j < art.x)
		{
			art.color = bit_color(art.tab_art[i][j]);
			if (art.tab_art[i] && ft_isdigit(art.tab_art[i][j]))
				draw_rect(art.mlx_img, (t_rect){
					(j * art.size) + art.posx, (i * art.size) + art.posy,
					art.size, art.size, art.color});
			j++;
		}
		i++;
	}
}

static void	save_ascii_scene(t_art art)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < art.y)
	{
		k = 0;
		while (k < art.x)
		{
			if (art.save[i] == '\n' || art.save[i] == '\0')
			{
				i++;
				break ;
			}
			if (!ft_isspace(art.save[i]) && art.save[i] != '\n')
				art.tab_art[j][k] = art.save[i];
			k++;
			i++;
		}
		j++;
	}
	render_art(art);
}

static void	init_ascii_scene(t_art art)
{
	int		i;

	i = 0;
	art.tab_art = ft_calloc(art.y + 1, sizeof(char *));
	if (!art.tab_art)
		return ;
	while (i < art.y)
	{
		art.tab_art[i] = ft_calloc(art.x, sizeof(char));
		if (!art.tab_art[i])
			return ;
		ft_memset(art.tab_art[i], EMPTY_ZONE, art.x);
		art.tab_art[i][art.x - 1] = '\0';
		i++;
	}
	save_ascii_scene(art);
	ft_free_multitab(art.tab_art);
}

void	init_ascii(t_art art)
{
	art.fd = open(art.file, O_RDONLY);
	art.save = ft_strdup("");
	art.line = get_next_line(art.fd);
	art.tab_art = NULL;
	if (art.line)
	{
		art.x = (int)ft_strlen(art.line);
		art.y = 0;
		while (art.line != NULL)
		{
			if (art.x < (int)ft_strlen(art.line))
				art.x = (int)ft_strlen(art.line);
			art.tmp = ft_strjoin(art.save, art.line);
			free(art.save);
			art.save = ft_strdup(art.tmp);
			free(art.tmp);
			free(art.line);
			art.line = get_next_line(art.fd);
			art.y++;
		}
		init_ascii_scene(art);
	}
	free_stuff(art.line);
	free_stuff(art.save);
	close(art.fd);
}
