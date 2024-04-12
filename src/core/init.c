/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:34:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 11:56:57 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_input(t_input *input)
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
	input->map_height = 0;
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
