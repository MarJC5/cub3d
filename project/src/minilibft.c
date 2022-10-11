/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:09:06 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 12:05:50 by jmartin          ###   ########.fr       */
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

int	encode_rgb(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
	return (alpha << 24 | red << 16 | green << 8 | blue);
}

int	chartohex(char *tab, int opacity)
{
	char	**split;
	int		hexret;

	split = ft_split(tab, ',');
	hexret = encode_rgb(opacity,
			ft_atoi(split[0]),
			ft_atoi(split[1]),
			ft_atoi(split[2]));
	free(split[2]);
	free(split[1]);
	free(split[0]);
	free(split);
	return (hexret);
}

int	ret_doublon(char *j, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (j[i] != '1')
		{
			free(j);
			return (ERR_PRESET);
		}
		i++;
	}
	free(j);
	return (SUCCESS);
}
