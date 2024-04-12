/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_newlines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:36:44 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 14:05:53 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Remove NO and SO textures newlines.
 *
 * This function remove the trailing newlines from the north and South textures.
 *
 * @param game game structure.
 * @return SUCCESS if remove successfull, or FAILURE if not.
 */
static int	remove_no_so_newlines(t_game *game)
{
	char	*tmp;

	if (ft_strchr(game->input->wall_no, '\n'))
	{
		tmp = game->input->wall_no;
		game->input->wall_no = ft_strndup(tmp, ft_strlen(tmp) - 1);
		if (!game->input->wall_no)
			return (print_error(ERR_MALLOC), FAILURE);
		free(tmp);
	}
	if (ft_strchr(game->input->wall_so, '\n'))
	{
		tmp = game->input->wall_so;
		game->input->wall_so = ft_strndup(tmp, ft_strlen(tmp) - 1);
		if (!game->input->wall_so)
			return (print_error(ERR_MALLOC), FAILURE);
		free(tmp);
	}
	return (SUCCESS);
}

/**
 * @brief Remove EA and WE textures newlines.
 *
 * This function remove the trailing newlines from the west and east textures.
 *
 * @param game game structure.
 * @return SUCCESS if remove successfull, or FAILURE if not.
 */
static int	remove_we_ea_newlines(t_game *game)
{
	char	*tmp;

	if (ft_strchr(game->input->wall_we, '\n'))
	{
		tmp = game->input->wall_we;
		game->input->wall_we = ft_strndup(tmp, ft_strlen(tmp) - 1);
		if (!game->input->wall_we)
			return (print_error(ERR_MALLOC), FAILURE);
		free(tmp);
	}
	if (ft_strchr(game->input->wall_ea, '\n'))
	{
		tmp = game->input->wall_ea;
		game->input->wall_ea = ft_strndup(tmp, ft_strlen(tmp) - 1);
		if (!game->input->wall_ea)
			return (print_error(ERR_MALLOC), FAILURE);
		free(tmp);
	}
	return (SUCCESS);
}

/**
 * @brief Remove the map newlines.
 *
 * This function remove the trailing newlines from all map lines.
 *
 * @param game game structure.
 * @return SUCCESS if remove successfull, or FAILURE if not.
 */
static int	remove_map_newlines(t_game *game)
{
	char	*tmp;
	int		i;

	i = 0;
	while (game->input->map[i])
	{
		if (ft_strchr(game->input->map[i], '\n'))
		{
			tmp = game->input->map[i];
			game->input->map[i] = ft_strndup(tmp, ft_strlen(tmp) - 1);
			if (!game->input->map[i])
				return (free(tmp), print_error(ERR_MALLOC), FAILURE);
			free(tmp);
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Remove the newlines.
 *
 * This function calls all the functions necessary to remove the newlines from
 * the wall textures and from the map.
 *
 * @param game game structure.
 * @return SUCCESS if remove successfull, or FAILURE if not.
 */
int	remove_newlines(t_game *game)
{
	if (remove_no_so_newlines(game) == FAILURE)
		return (FAILURE);
	if (remove_we_ea_newlines(game) == FAILURE)
		return (FAILURE);
	if (remove_map_newlines(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
