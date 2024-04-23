/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:51:48 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/23 15:55:57 by aurlic           ###   ########.fr       */
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
	if (game->draw->textures)
		free_matrix_safe((char **)game->draw->textures);
	if (game->pixels)
		free_matrix_safe((char **)game->pixels);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		(mlx_destroy_display(game->mlx), free(game->mlx));
	free(game->player);
	free(game->ray);
	free(game->draw);
	free(game->img);
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
