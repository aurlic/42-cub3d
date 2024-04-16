/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:14:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/16 11:00:08 by aurlic           ###   ########.fr       */
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
	game.libx->mlx = mlx_init();
	if (!game.libx->mlx)
		(free_game(&game), exit(EXIT_FAILURE));
	game.libx->win = mlx_new_window(game.libx->mlx, WIN_W, WIN_H, "cub2debile");
	if (!game.libx->win)
		(free_game(&game), exit(EXIT_FAILURE));
	// mlx_hook(game.window, 2, 1L << 0, keypress_hook, &game);
	mlx_hook(game.libx->win, MOUSE_CLOSE, 0L, exit_game, &game);
	mlx_loop(game.libx->mlx);
	return (free_game(&game), EXIT_SUCCESS);
}
