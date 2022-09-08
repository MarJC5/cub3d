/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 10:52:57 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/08 15:21:14 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	bit_color(int ref)
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

void	render_art(t_art art, char **tab_art)
{
	int	i;
	int	j;

	i = 0;
	while (i < art.y)
	{
		j = 0;
		while (j < art.x)
		{
			art.color = bit_color(tab_art[i][j]);
			if (ft_isdigit(tab_art[i][j]))
				draw_rect(art.mlx_img, (t_rect){
					(j * art.size) + art.posx, (i * art.size) + art.posx,
					art.size, art.size, art.color});
			j++;
		}
		i++;
	}
}

void	save_ascii_scene(t_art art, char **tab_art)
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
				tab_art[j][k] = art.save[i];
			k++;
			i++;
		}
		j++;
	}
	render_art(art, tab_art);
}

void	init_ascii_scene(t_art art)
{
	int		i;
	char	**tab_art;

	i = 0;
	tab_art = ft_calloc(art.y, sizeof(char *));
	if (!tab_art)
		return ;
	while (i < art.y)
	{
		tab_art[i] = ft_calloc(art.x, sizeof(char));
		if (!tab_art[i])
			return ;
		ft_memset(tab_art[i], EMPTY_ZONE, art.x);
		tab_art[i][art.x - 1] = '\0';
		i++;
	}
	save_ascii_scene(art, tab_art);
}

void	init_ascii(t_art art)
{
	art.fd = open(art.file, O_RDONLY);
	art.save = ft_strdup("");
	art.line = get_next_line(art.fd);
	art.x = (int)ft_strlen(art.line);
	art.y = 0;
	while (art.line != NULL)
	{
		if (art.x < (int)ft_strlen(art.line))
			art.x = (int)ft_strlen(art.line);
		art.tmp = ft_strjoin(art.save, art.line);
		free(art.save);
		art.save = ft_strdup(art.tmp);
		free(art.line);
		art.line = get_next_line(art.fd);
		art.y++;
	}
	close(art.fd);
	free(art.line);
	free(art.tmp);
	init_ascii_scene(art);
	free(art.save);
}
