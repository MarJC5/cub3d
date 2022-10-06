/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:31 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/06 07:40:13 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	printerr(char *err)
{
	ft_putendl_fd(err, 2);
	return (EXIT_FAILURE);
}

int	printinvalid(int errno)
{
	if (errno > SUCCESS)
		printerr(ERROR);
	if (errno == ERR_PRESET)
		printerr(WRONG_PRESET);
	if (errno == ERR_CHAR)
		printerr(WRONG_CHAR);
	if (errno == ERR_MAP)
		printerr(WRONG_MAP);
	if (errno == ERR_NAME)
		printerr(WRONG_NAME);
	if (errno == ERR_UNCLOSED)
		printerr(MAP_UNCLOSED);
	return (errno);
}
