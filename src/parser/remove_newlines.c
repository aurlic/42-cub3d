/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_newlines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:36:44 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 11:59:29 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
