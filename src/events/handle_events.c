/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:15:04 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 15:54:03 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/**
 * @brief Handle events when a key is pressed.
 *
 * This function updates values related to the angle and the movement
 * when a corresponding key is pressed.
 *
 * @param key key pressed.
 * @param game game structure.
 * @return SUCCESS when done.
 */
int	handle_keypress(int key, t_game *game)
{
	if (key == XK_Escape)
		exit_game(game);
	if (key == XK_w)
		game->player->move_y = 1;
	if (key == XK_a)
		game->player->move_x = -1;
	if (key == XK_s)
		game->player->move_y = -1;
	if (key == XK_d)
		game->player->move_x = 1;
	if (key == XK_Left)
		game->player->rotate -= 1;
	if (key == XK_Right)
		game->player->rotate += 1;
	return (SUCCESS);
}

/**
 * @brief Handle events when a key is released.
 *
 * This function resets values related to the angle and the movement back to 0
 * when a corresponding key is pressed.
 *
 * @param key key pressed.
 * @param game game structure.
 * @return SUCCESS when done.
 */
int	handle_keyrelease(int key, t_game *game)
{
	if (key == XK_Escape)
		exit_game(game);
	if (key == XK_w && game->player->move_y == 1)
		game->player->move_y = 0;
	if (key == XK_a && game->player->move_x == -1)
		game->player->move_x = 0;
	if (key == XK_s && game->player->move_y == -1)
		game->player->move_y = 0;
	if (key == XK_d && game->player->move_x == 1)
		game->player->move_x = 0;
	if (key == XK_Left && game->player->rotate <= 1)
		game->player->rotate = 0;
	if (key == XK_Right && game->player->rotate >= 1)
		game->player->rotate = 0;
	return (SUCCESS);
}

/**
 * @brief Start hook to catch input.
 *
 * This function start hook function that will catch keypress and keyrelease
 * events, and mouse click.
 *
 * @param game game structure.
 */
void	handle_events(t_game *game)
{
	mlx_hook(game->win, MOUSE_CLOSE, 0L, exit_game, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, handle_keyrelease, game);
}
