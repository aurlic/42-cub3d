/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:15:04 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/23 16:47:19 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	handle_events(t_game *game)
{
	mlx_hook(game->win, MOUSE_CLOSE, 0L, exit_game, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, handle_keypress, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, handle_keyrelease, game);
}
