/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 11:25:10 by jmartin           #+#    #+#             */
/*   Updated: 2022/08/24 19:07:56 by jmartin          ###   ########.fr       */
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
	return (errno);
}
