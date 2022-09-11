/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:04:35 by jmartin           #+#    #+#             */
/*   Updated: 2022/09/09 15:42:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

float	degtorad(float ang)
{
	return (ang * M_PI / 180.0);
}

float	radtodeg(float ang)
{
	return (ang * (180.0 / M_PI));
}

int	fixang(int ang)
{
	if (ang > 359)
		ang -= 360;
	if (ang < 0)
		ang += 360;
	return (ang);
}
