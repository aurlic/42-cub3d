/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:48 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 11:42:36 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
}

void	free_game(t_game *game)
{
	if (game->input->content)
		free_matrix_safe(game->input->content);
	if (game->input->map)
		free_matrix_safe(game->input->map);
	if (game->input->wall_no)
		free(game->input->wall_no);
	if (game->input->wall_so)
		free(game->input->wall_so);
	if (game->input->wall_we)
		free(game->input->wall_we);
	if (game->input->wall_ea)
		free(game->input->wall_ea);
	free(game->input);
}
