/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:14:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/11 12:03:49 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_input(t_input *input)
{
	input->content = NULL;
	input->map = NULL;
	input->wall_no = NULL;
	input->wall_so = NULL;
	input->wall_we = NULL;
	input->wall_ea = NULL;
	input->color_f[0] = -1;
	input->color_f[1] = -1;
	input->color_f[2] = -1;
	input->color_c[0] = -1;
	input->color_c[1] = -1;
	input->color_c[2] = -1;
	input->map_h = 0;
	input->map_w = 0;
	input->map_start = 0;
	input->file_lines = 0;
}

int	init_game(t_game *game)
{
	t_input	*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return (print_error(ERR_MALLOC), FAILURE);
	init_input(input);
	game->input = input;
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		(print_error(ERR_WRONG_ARG_NB), exit(EXIT_FAILURE));
	if (init_game(&game) == FAILURE)
		exit(EXIT_FAILURE);
	if (parser(&game, av) == FAILURE)
		exit(TMP);
	return (EXIT_SUCCESS);
}
