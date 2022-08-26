/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fpf_map_preset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/24 19:14:53 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (*s1 && *s2)
	{
		while (s1[i] && (s1[i] == s2[i]))
			i++;
		return (s1[i] - s2[i]);
	}
	return (-1);
}

int	ft_isspace(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int splitoi(char *tab)
{
	char    **split;
	int     hexret;
	int     i;

	split = ft_split(tab, ',');
	hexret = encode_rgb(ft_atoi(split[0]),
	                    ft_atoi(split[1]),
	                    ft_atoi(split[2]));
	i = 3;
	while (split[i])
		free(split[i--]);
	free(split);
	return (hexret);
}
