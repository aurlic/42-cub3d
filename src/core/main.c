/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:14:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/23 16:55:40 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display(t_game *game)
{
	
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		(print_error(ERR_WRONG_ARG_NB), exit(EXIT_FAILURE));
	if (init_game(&game) == FAILURE)
		exit(EXIT_FAILURE);
	if (parser(&game, av) == FAILURE)
		(free_game(&game), exit(EXIT_FAILURE));
	game.mlx = mlx_init();
	if (!game.mlx)
		(free_game(&game), exit(EXIT_FAILURE));
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "cub2debile");
	if (!game.win)
		(free_game(&game), exit(EXIT_FAILURE));
	if (load_textures(&game) == FAILURE)
		(free_game(&game), exit(EXIT_FAILURE));
	if (raycasting(&game) == FAILURE)
		(free_game(&game), exit(EXIT_FAILURE));
	handle_events(&game);
	mlx_loop_hook(game.mlx, display, &game);
	mlx_loop(game.mlx);
	return (free_game(&game), EXIT_SUCCESS);
}
