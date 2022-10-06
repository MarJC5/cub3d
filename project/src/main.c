/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 16:08:59 by jmartin           #+#    #+#             */
/*   Updated: 2022/10/04 11:29:26 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (EXIT_FAILURE);
	if (argc == 2)
	{
		init_default(game);
		if (init_map(game, argv[argc - 1]) == FAILURE)
			return (EXIT_FAILURE);
	}
	else if (argc == 1 || argc > 2)
		printinvalid(ERR_NAME);
	free_map(game);
	free(game);
	return (EXIT_SUCCESS);
}
