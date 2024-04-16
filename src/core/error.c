/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:48 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/16 11:00:32 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print an error message.
 *
 * @param err_msg error message to print.
 */
void	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, STDERR_FILENO);
}

/**
 * @brief Free the game structure.
 *
 * @param game game structure.
 */
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
	if (game->libx->win)
		mlx_destroy_window(game->libx->mlx, game->libx->win);
	if (game->libx->mlx)
		(mlx_destroy_display(game->libx->mlx), free(game->libx->mlx));
	free(game->libx);
	free(game->input);
}

/**
 * @brief Free and exit the game.
 *
 * @param game game structure.
 */
int	exit_game(t_game *game)
{
	free_game(game);
	exit(EXIT_SUCCESS);
}
