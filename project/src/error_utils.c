/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:31 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/11 15:35:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	printerr(char *err)
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
	if (errno == ERR_TEXT)
		printerr(MAP_CHAR);
	if (errno == ERR_PLAYER)
		printerr(WRONG_PLAY);
	if (errno == ERR_FD)
		printerr(WRONG_FILE);
	return (errno);
}
