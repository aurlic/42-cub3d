/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:14:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 14:30:08 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		(print_error(ERR_WRONG_ARG_NB), exit(EXIT_FAILURE));
	if (init_game(&game) == FAILURE)
		exit(EXIT_FAILURE);
	if (parser(&game, av) == FAILURE)
		(free_game(&game), exit(EXIT_FAILURE));
	return (free_game(&game), EXIT_SUCCESS);
}
